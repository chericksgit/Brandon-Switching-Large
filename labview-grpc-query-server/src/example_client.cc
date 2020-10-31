//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <measurement_service.grpc.pb.h>
#include <sstream>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using grpc::Channel;
using grpc::ClientContext;
using grpc::Status;
using namespace std;
using namespace measurementservice;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class QueryClient
{
public:
    QueryClient(shared_ptr<Channel> channel);

public:
    void Invoke(const string& command, const string& parameters);
    string Query(const string &command);
    unique_ptr<grpc::ClientReader<ServerEvent>> Register(const string& eventName);

public:
    ClientContext m_context;
    unique_ptr<MeasurementService::Stub> m_Stub;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
QueryClient::QueryClient(shared_ptr<Channel> channel)
    : m_Stub(MeasurementService::NewStub(channel))
{        
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void QueryClient::Invoke(const string& command, const string& parameters)
{
    InvokeRequest request;
    request.set_command(command);
    request.set_parameter(parameters);

    ClientContext context;
    InvokeResponse reply;
    Status status = m_Stub->Invoke(&context, request, &reply);
    if (!status.ok())
    {
        cout << status.error_code() << ": " << status.error_message() << endl;
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string QueryClient::Query(const string &command)
{
    QueryRequest request;
    request.set_query(command);
    QueryResponse reply;
    ClientContext context;

    Status status = m_Stub->Query(&context, request, &reply);

    if (status.ok())
    {
        return reply.message();
    }
    else
    {
        cout << status.error_code() << ": " << status.error_message() << endl;
        return "RPC failed";
    }
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
unique_ptr<grpc::ClientReader<ServerEvent>> QueryClient::Register(const string& eventName)
{
    RegistrationRequest request;
    request.set_eventname(eventName);

    return m_Stub->Register(&m_context, request);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string GetServerAddress(int argc, char** argv)
{
    string target_str;
    string arg_str("--target");
    if (argc > 1)
    {
        string arg_val = argv[1];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != string::npos)
        {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=')
            {
                target_str = arg_val.substr(start_pos + 1);
            }
            else
            {
                cout << "The only correct argument syntax is --target=" << endl;
                return 0;
            }
        }
        else
        {
            cout << "The only acceptable argument is --target=" << endl;
            return 0;
        }
    }
    else
    {
        target_str = "localhost:50051";
    }
    return target_str;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
string GetCertPath(int argc, char** argv)
{
    string cert_str;
    string arg_str("--cert");
    if (argc > 2)
    {
        string arg_val = argv[2];
        size_t start_pos = arg_val.find(arg_str);
        if (start_pos != string::npos)
        {
            start_pos += arg_str.size();
            if (arg_val[start_pos] == '=')
            {
                cert_str = arg_val.substr(start_pos + 1);
            }
            else
            {
                cout << "The only correct argument syntax is --cert=" << endl;
                return 0;
            }
        }
        else
        {
            cout << "The only acceptable argument is --cert=" << endl;
            return 0;
        }
    }
    return cert_str;
}

std::string read_keycert( const std::string& filename)
{	
	std::string data;
	std::ifstream file(filename.c_str(), std::ios::in);
	if (file.is_open())
	{
		std::stringstream ss;
		ss << file.rdbuf();
		file.close();
		data = ss.str();
	}
	return data;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
int main(int argc, char **argv)
{
    auto target_str = GetServerAddress(argc, argv);
    auto certificatePath = GetCertPath(argc, argv);

    shared_ptr<grpc::ChannelCredentials> creds;
    if (!certificatePath.empty())
    {
        std::string cacert = read_keycert(certificatePath);
        grpc::SslCredentialsOptions ssl_opts;
        ssl_opts.pem_root_certs=cacert;
        creds = grpc::SslCredentials(ssl_opts);
    }
    else
    {
        creds = grpc::InsecureChannelCredentials();
    }
    auto channel = grpc::CreateChannel(target_str, creds);
    QueryClient client(channel);

    auto result = client.Query("Uptime");
    cout << "Server uptime: " << result << endl;

    {
        ClientContext ctx;
        ConfigRequest configRequest;
        ConfigAck configResponse;

        configRequest.set_smuresourcename("SMU");
		configRequest.set_smuchannels("0");
		configRequest.set_smusourcemode(1021);
		configRequest.set_smuoutputfunction(1007);
		configRequest.set_smusourcetransientresponse(1039);
		configRequest.set_smucurrent(1.0);
		configRequest.set_smucurrentlevelrange(1.0);
		configRequest.set_smumeasurementsense(1008);
		configRequest.set_smumeasurementaperturetime(0.010);
		configRequest.set_smusourceadvancedsourcedelay(0.000100);
		configRequest.set_smuvoltage(6);
		configRequest.set_smusourceadvancedsequenceloopcount(127);
		configRequest.set_smumeasurementadvanceddcnoiserejection(1044);
		configRequest.set_smusequencename("MySequence");
		configRequest.set_scanlist("SCANALL");
		configRequest.set_dmmresourcename("DMM");
		configRequest.set_dmmfunction(0);
		configRequest.set_dmmresolution(0.1);
		configRequest.set_dmmrange(0.1);
		configRequest.set_dmmsamplecount(0);
		configRequest.set_dmmaperturetimeunit(0);
		configRequest.set_dmmaperturetime(0.010);
		configRequest.set_dmmnumberofaverages(1);
		configRequest.set_dmmautozero(0);
		configRequest.set_dmmadccalibration(0);
		configRequest.set_dmmsettletime(0.0001);
		configRequest.set_dmmcontrolaction(0);
        configRequest.set_dmmvoltagefaultupperlimit(0.000050);
        configRequest.set_applicationnumberofweldchannels(127);
        cout << "Configuring measurement" << endl;
        client.m_Stub->SendConfig(&ctx, configRequest, &configResponse);
        cout << "Config sent: " << configResponse.acknowledge() << endl;
    }

//        client.Invoke("Restore JSON", "");

    {
        auto reader = client.Register("Heartbeat");
        int count = 0;
        ServerEvent event;
        while (reader->Read(&event))
        {
            cout << "Server Event: " << event.eventdata() << endl;
            count += 1;
            if (count == 5)
            {
                client.Invoke("Reset", "");
            }
        }
        Status status = reader->Finish();
        cout << "Server notifications complete" << endl;
    }

//    {
//        ClientContext ctx;
//        ErrorOut error;
//        auto reader = client.m_Stub->StreamError(&ctx, ErrorRequest());
//        while (reader->Read(&error))
//        {
//            cout << "Server Error: " << error.errmessage() << ", " << error.errcode() << endl;
//        }
//        Status status = reader->Finish();
//        cout << "Server error test complete" << endl;
//    }

    cout << "Performing 4 probe measurement" << endl;
    {
        auto startTime = chrono::steady_clock::now();
        ClientContext ctx;
        FourProbeRequest request;
        FourProbeData data;
        client.m_Stub->PerformFourProbeMeasurement(&ctx, request, &data);
        auto measurements = data.data();
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "4 probe measurement took: " << elapsed.count() << " milliseconds" << endl;
        cout << "Received " << measurements.size() << " measurements." << endl;
        cout << "First Results: "  << endl;
        int x=0;
        for (auto it = measurements.begin();  it != measurements.end(); ++it)
        {
            cout << "  -V:" << (*it).negvoltage() << " +V:" << (*it).posvoltage() << " -C" << (*it).negcurrent() << " +C" << (*it).poscurrent() << " Z:" << (*it).impedance() << endl;
            if (++x == 10)
            {
                break;
            }
        }
    }
    cout << "Performing Streaming 4 probe measurement" << endl;
    {
        auto startTime = chrono::steady_clock::now();
        ClientContext ctx;
        FourProbeRequest request;
        FourProbeRaw data;
        auto measurementReader = client.m_Stub->StreamFourProbeMeasurement(&ctx, request);
        int x=0;
        cout << "First Four Probe Results: "  << endl;
        while (measurementReader->Read(&data))
        {
            if (++x <= 21)
            {
                cout << "  -V:" << data.negvoltage() << " +V:" << data.posvoltage() << " -C" << data.negcurrent() << " +C" << data.poscurrent() << " Z:" << data.impedance() << endl;
            }
        }
        auto endTime = chrono::steady_clock::now();
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(endTime - startTime);
        cout << "4 probe measurement took: " << elapsed.count() << " milliseconds" << endl;
        cout << "Received " << x << " measurements." << endl;
    }
}
