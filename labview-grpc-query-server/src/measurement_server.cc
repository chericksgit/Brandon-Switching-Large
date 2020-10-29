//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <measurement_server.h>
#include <thread>
#include <sstream>
#include <fstream>
#include <iostream>

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using namespace std;
using namespace measurementservice;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
LabVIEWMeasurementServer::LabVIEWMeasurementServer(LabVIEWMeasurementServerInstance* instance)
    : m_Instance(instance)
{    
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::SendConfig(ServerContext* context, const ConfigRequest* request, ConfigAck* response)
{	
    auto data = new SendConfigData(context, request, response);
    m_Instance->SendEvent("MeasurementService_SendConfig", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::PerformFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, FourProbeData* response)
{	
    auto data = new FourProbeMeasurementData(context, request, response);
    m_Instance->SendEvent("MeasurementService_FourProbeMeasurement", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::StreamFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, ServerWriter<FourProbeRaw>* writer)
{	
    auto data = new FourProbeMeasurementData(context, request, writer);
    m_Instance->SendEvent("MeasurementService_StreamFourProbeMeasurement", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::Invoke(ServerContext* context, const InvokeRequest* request, InvokeResponse* response)
{
    auto data = new InvokeData(context, request, response);
    m_Instance->SendEvent("MeasurementService_Invoke", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::Query(ServerContext* context, const QueryRequest* request, QueryResponse* response) 
{
    auto data = new QueryData(context, request, response);
    m_Instance->SendEvent("MeasurementService_Query", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::StreamError(ServerContext* context, const ErrorRequest* request, ServerWriter<ErrorOut>* writer)
{
	auto data = new StreamErrorData(context, request, writer);	
    m_Instance->SendEvent("MeasurementService_StreamError", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
Status LabVIEWMeasurementServer::Register(ServerContext* context, const RegistrationRequest* request, ServerWriter<ServerEvent>* writer)
{
    auto data = new RegistrationRequestData(context, request, writer);
    m_Instance->SendEvent("MeasurementService_Register", data);
    data->WaitForComplete();
    delete data;
    return Status::OK;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void LabVIEWMeasurementServerInstance::RegisterEvent(string name, LVUserEventRef item)
{    
	m_RegisteredServerMethods.insert(pair<string,LVUserEventRef>(name, item));
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void LabVIEWMeasurementServerInstance::SendEvent(string name, EventData* data)
{
	auto occurrence = m_RegisteredServerMethods.find(name);
	if (occurrence != m_RegisteredServerMethods.end())
	{
		if (occurrence->second == 0)
		{
			cout << "invalid occurrence reference" << endl;
		}
		OccurServerEvent(occurrence->second, data);
	}
	else
	{
		cout << "Event NOT Registered: " << name << endl;
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
int LabVIEWMeasurementServerInstance::Run(string address, string serverCertificatePath, string serverKeyPath)
{
	ServerStartEventData serverStarted;
    new thread(RunServer, address, serverCertificatePath, serverKeyPath, this, &serverStarted);
	serverStarted.WaitForComplete();
	return serverStarted.serverStartStatus;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
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
void LabVIEWMeasurementServerInstance::RunServer(
	string address, 
	string serverCertificatePath, 
	string serverKeyPath, 
	LabVIEWMeasurementServerInstance* instance,
	ServerStartEventData* serverStarted)
{
	string server_address;
    if (address.length() != 0)
    {
        server_address = address;
    }
    if (server_address.length() == 0)
    {
        server_address = "0.0.0.0:50051";
    }

	LabVIEWMeasurementServer service(instance);
	grpc::EnableDefaultHealthCheckService(true);
	grpc::reflection::InitProtoReflectionServerBuilderPlugin();
	ServerBuilder builder;

	std::shared_ptr<grpc::ServerCredentials> creds;
	if (serverCertificatePath.length() > 1)
	{
		std::string servercert = read_keycert(serverCertificatePath);
		std::string serverkey = read_keycert(serverKeyPath);

		grpc::SslServerCredentialsOptions::PemKeyCertPair pkcp;
		pkcp.private_key = serverkey;
		pkcp.cert_chain = servercert;

		grpc::SslServerCredentialsOptions ssl_opts;
		ssl_opts.pem_root_certs="";
		ssl_opts.pem_key_cert_pairs.push_back(pkcp);

		creds = grpc::SslServerCredentials(ssl_opts);
	}
	else
	{
		creds = grpc::InsecureServerCredentials();
	}

	// Listen on the given address without any authentication mechanism.
	builder.AddListeningPort(server_address, creds);
	// Register "service" as the instance through which we'll communicate with
	// clients. In this case it corresponds to an *synchronous* service.
	builder.RegisterService(&service);
	// Finally assemble the server.
	instance->m_Server = builder.BuildAndStart();

	if (instance->m_Server != NULL)
	{
		cout << "Server listening on " << server_address << endl;
		serverStarted->NotifyComplete();
		instance->m_Server->Wait();
	}
	else
	{
		cout << "Server failed to start!" << endl;
		serverStarted->serverStartStatus = -1;
		serverStarted->NotifyComplete();
	}
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void LabVIEWMeasurementServerInstance::StopServer()
{
	if (m_Server != NULL)
	{
		m_Server->Shutdown();
		m_Server->Wait();
		m_Server = NULL;
	}
}
