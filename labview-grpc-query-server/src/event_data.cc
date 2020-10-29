//---------------------------------------------------------------------
//---------------------------------------------------------------------
#include <measurement_server.h>

//---------------------------------------------------------------------
//---------------------------------------------------------------------
using namespace std;
using namespace measurementservice;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
EventData::EventData(ServerContext* _context)
{
    _isComplete = false;
    context = _context;    
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void EventData::WaitForComplete()
{    
    std::unique_lock<std::mutex> lck(_lockMutex);
    if (_isComplete)    
    {
        return;
    }
    _lock.wait(lck);
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void EventData::NotifyComplete()
{    
    cout << "EventData::NotifyComplete" << endl;
	std::unique_lock<std::mutex> lck(_lockMutex);
    _isComplete = true;
	_lock.notify_all();
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
ServerStartEventData::ServerStartEventData()
    : EventData(NULL)
{
    serverStartStatus = 0;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
StreamErrorData::StreamErrorData(ServerContext* context, const ErrorRequest* request, ServerWriter<ErrorOut>* writer)
    : EventData(context)
{
    _request = request;
    _writer = writer;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
SendConfigData::SendConfigData(ServerContext* context, const ConfigRequest* request, ConfigAck* response)
    : EventData(context)
{
    _request = request;
    _response = response;    
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
FourProbeMeasurementData::FourProbeMeasurementData(ServerContext* _context, const FourProbeRequest* _request, FourProbeData* _response)
    : EventData(_context)
{
    request = _request;
    writer = nullptr;
    response = _response;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
FourProbeMeasurementData::FourProbeMeasurementData(ServerContext* _context, const FourProbeRequest* _request, ::grpc::ServerWriter<FourProbeRaw>* _writer)
    : EventData(_context)
{
    request = _request;
    writer = _writer;
    response = nullptr;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
InvokeData::InvokeData(ServerContext* _context, const InvokeRequest* _request, InvokeResponse* _response)
    : EventData(_context)
{
    request = _request;
    response = _response;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
QueryData::QueryData(ServerContext* _context, const QueryRequest* _request, QueryResponse* _response)
    : EventData(_context)
{    
    request = _request;
    response = _response;
}

//---------------------------------------------------------------------
//---------------------------------------------------------------------
RegistrationRequestData::RegistrationRequestData(ServerContext* _context, const RegistrationRequest* _request, ::grpc::ServerWriter<ServerEvent>* _writer)
    : EventData(_context)
{
    request = _request;
    eventWriter = _writer;
}

