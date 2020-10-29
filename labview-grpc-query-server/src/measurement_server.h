//---------------------------------------------------------------------
// Implementation objects for the LabVIEW implementation of the
// gRPC MeasurementService
//---------------------------------------------------------------------
#pragma once

#ifdef __WIN32__
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <measurement_service.grpc.pb.h>
#include <condition_variable>

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerContext;
using grpc::Status;
using grpc::ServerWriter;
using namespace measurementservice;
using namespace std;

#ifdef _WIN32
    #define LIBRARY_EXPORT extern "C" __declspec(dllexport)
#else
    #define LIBRARY_EXPORT extern "C"
#endif

//---------------------------------------------------------------------
// LabVIEW definitions
//---------------------------------------------------------------------
typedef int32_t MagicCookie;
typedef MagicCookie LVRefNum;
typedef MagicCookie LVUserEventRef;

typedef struct {
	int32_t cnt; /* number of bytes that follow */
	char str[1]; /* cnt bytes */
} LStr, * LStrPtr, ** LStrHandle;


typedef struct {
	int32_t cnt; /* number of bytes that follow */
#ifndef _PS_4
    int32_t padding;
#endif
	int8_t str[1]; /* cnt bytes */
} LV1DArray, * LV1DArrayPtr, ** LV1DArrayHandle;

//---------------------------------------------------------------------
// LabVIEW definitions
//---------------------------------------------------------------------
typedef void* LVgRPCid;
typedef void* LVgRPCServerid;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class EventData
{
public:
    EventData(ServerContext* context);

private:
    bool _isComplete;
	mutex _lockMutex;
	condition_variable _lock;

public:
	ServerContext* context;

public:
    void WaitForComplete();
    void NotifyComplete();
};

class LabVIEWMeasurementServerInstance;

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class LabVIEWMeasurementServer final : public measurementservice::MeasurementService::Service
{
public:
    LabVIEWMeasurementServer(LabVIEWMeasurementServerInstance* instance);
    void SopServer();
    void RegisterEvent(string eventName, LVUserEventRef reference);

    // Overrides
    Status Invoke(ServerContext* context, const InvokeRequest* request, InvokeResponse* response) override;
    Status Query(ServerContext* context, const QueryRequest* request, QueryResponse* response) override; 
    Status Register(ServerContext* context, const RegistrationRequest* request, ServerWriter<ServerEvent>* writer) override;
    Status StreamError(ServerContext* context, const ErrorRequest* request, ServerWriter<ErrorOut>* writer) override;
    Status SendConfig(ServerContext* context, const ConfigRequest* request, ConfigAck* response) override;
    Status PerformFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, FourProbeData* response) override;
    Status StreamFourProbeMeasurement(ServerContext* context, const FourProbeRequest* request, ServerWriter<FourProbeRaw>* writer) override;

private:
    LabVIEWMeasurementServerInstance* m_Instance;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class ServerStartEventData : public EventData
{
public:
    ServerStartEventData();

public:
    int serverStartStatus;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class StreamErrorData : public EventData
{
public:
    StreamErrorData(ServerContext* context, const ErrorRequest* request, ServerWriter<ErrorOut>* writer);

public:
    const ErrorRequest* _request;
    ServerWriter<ErrorOut>* _writer;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class SendConfigData : public EventData
{
public:
    SendConfigData(ServerContext* context, const ConfigRequest* request, ConfigAck* response);

public:
    const ConfigRequest* _request;
    ConfigAck* _response;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class FourProbeMeasurementData : public EventData
{
public:
    FourProbeMeasurementData(ServerContext* context, const FourProbeRequest* request, ServerWriter<FourProbeRaw>* writer);
    FourProbeMeasurementData(ServerContext* context, const FourProbeRequest* request, FourProbeData* response);

public:
	const FourProbeRequest* request;
	grpc::ServerWriter<FourProbeRaw>* writer;
	FourProbeData* response;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class InvokeData : public EventData
{
public:
    InvokeData(ServerContext* context, const InvokeRequest* request, InvokeResponse* response);

public:
	const InvokeRequest* request;
	InvokeResponse* response;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class QueryData : public EventData
{
public:
    QueryData(ServerContext* context, const QueryRequest* request, QueryResponse* response);

public:
	const QueryRequest* request;
	QueryResponse* response;
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
class RegistrationRequestData : public EventData
{
public:
    RegistrationRequestData(ServerContext* context, const RegistrationRequest* request, ServerWriter<measurementservice::ServerEvent>* writer);

public:
    const measurementservice::RegistrationRequest* request;
    grpc::ServerWriter<measurementservice::ServerEvent>* eventWriter;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
class LabVIEWMeasurementServerInstance
{
public:
    int Run(string address, string serverCertificatePath, string serverKeyPath);
    void StopServer();
    void RegisterEvent(string eventName, LVUserEventRef reference);
    void SendEvent(string name, EventData* data);

private:
    unique_ptr<Server> m_Server;
    map<string, LVUserEventRef> m_RegisteredServerMethods;

private:
    static void RunServer(string address, string serverCertificatePath, string serverKeyPath, LabVIEWMeasurementServerInstance* instance, ServerStartEventData* serverStarted);
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVErrorOutData
{
  int errCode;
  LStrHandle errMessage;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVConfigRequest
{
  LStrHandle SMUResourceName;
  LStrHandle SMUChannels;
  int32_t SMUSourceMode;
  int32_t SMUOutputFunction;
  int32_t SMUSourceTransientResponse;
  float SMUCurrent;
  float SMUCurrentLevelRange;
  int32_t SMUMeasurementSense;
  float SMUMeasurementApertureTime;
  float SMUSourceAdvancedSourceDelay;
  float SMUVoltage;
  int32_t SMUSourceAdvancedSequenceLoopCount;
  int32_t SMUMeasurementAdvancedDCNoiseRejection;
  LStrHandle SMUSequenceName;
  LStrHandle ScanList;
  LStrHandle DMMResourceName;
  int32_t DMMFunction;
  float DMMResolution;
  float DMMRange;
  int32_t DMMSampleCount;
  int32_t DMMApertureTimeUnit;
  float DMMApertureTime;
  int32_t DMMNumberOfAverages;
  int32_t DMMAutoZero;
  int32_t DMMADCCalibration;
  float DMMSettleTime;
  int32_t DMMControlAction;
  float DMMVoltageFaultUpperLimit;
  int32_t ApplicationNumberOfWeldChannels;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVConfigAck
{
  bool acknowledge;
};


//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVFourProbeRawData
{
  double posVoltage;
  double posCurrent;
  double negVoltage;
  double negCurrent;
  double impedance;
  LVErrorOutData error;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVFourProbeResponse
{
    LV1DArrayHandle results;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVInvokeRequest
{
    LStrHandle command;
    LStrHandle parameter;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVInvokeResponse
{
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVQueryRequest
{
    LStrHandle query;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVQueryResponse
{
    LStrHandle message;
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVRegistrationRequest
{
    LStrHandle eventName;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
struct LVServerEvent
{
    LStrHandle eventData;
    int32_t serverId;
    int32_t status;
};

//---------------------------------------------------------------------
//---------------------------------------------------------------------
void OccurServerEvent(LVUserEventRef event, EventData* data);
