<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="19008000">
	<Item Name="My Computer" Type="My Computer">
		<Property Name="server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="server.tcp.port" Type="Int">0</Property>
		<Property Name="server.tcp.serviceName" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.tcp.serviceName.default" Type="Str">My Computer/VI Server</Property>
		<Property Name="server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="specify.custom.address" Type="Bool">false</Property>
		<Item Name="Dependencies" Type="Dependencies"/>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
	<Item Name="NI-PXIe-8861-031E42AB" Type="RT PXI Chassis">
		<Property Name="alias.name" Type="Str">NI-PXIe-8861-031E42AB</Property>
		<Property Name="alias.value" Type="Str">169.254.111.217</Property>
		<Property Name="CCSymbols" Type="Str">TARGET_TYPE,RT;OS,Linux;CPU,x64;</Property>
		<Property Name="host.ResponsivenessCheckEnabled" Type="Bool">true</Property>
		<Property Name="host.ResponsivenessCheckPingDelay" Type="UInt">5000</Property>
		<Property Name="host.ResponsivenessCheckPingTimeout" Type="UInt">1000</Property>
		<Property Name="host.TargetCPUID" Type="UInt">9</Property>
		<Property Name="host.TargetOSID" Type="UInt">19</Property>
		<Property Name="target.cleanupVisa" Type="Bool">false</Property>
		<Property Name="target.FPProtocolGlobals_ControlTimeLimit" Type="Int">300</Property>
		<Property Name="target.getDefault-&gt;WebServer.Port" Type="Int">80</Property>
		<Property Name="target.getDefault-&gt;WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.IOScan.Faults" Type="Str"></Property>
		<Property Name="target.IOScan.NetVarPeriod" Type="UInt">100</Property>
		<Property Name="target.IOScan.NetWatchdogEnabled" Type="Bool">false</Property>
		<Property Name="target.IOScan.Period" Type="UInt">10000</Property>
		<Property Name="target.IOScan.PowerupMode" Type="UInt">0</Property>
		<Property Name="target.IOScan.Priority" Type="UInt">0</Property>
		<Property Name="target.IOScan.ReportModeConflict" Type="Bool">true</Property>
		<Property Name="target.IsRemotePanelSupported" Type="Bool">true</Property>
		<Property Name="target.RTCPULoadMonitoringEnabled" Type="Bool">true</Property>
		<Property Name="target.RTDebugWebServerHTTPPort" Type="Int">8001</Property>
		<Property Name="target.RTTarget.ApplicationPath" Type="Path">/c/ni-rt/startup/startup.rtexe</Property>
		<Property Name="target.RTTarget.EnableFileSharing" Type="Bool">true</Property>
		<Property Name="target.RTTarget.IPAccess" Type="Str">+*</Property>
		<Property Name="target.RTTarget.LaunchAppAtBoot" Type="Bool">false</Property>
		<Property Name="target.RTTarget.VIPath" Type="Path">/home/lvuser/natinst/bin</Property>
		<Property Name="target.server.app.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.control.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.server.tcp.access" Type="Str">+*</Property>
		<Property Name="target.server.tcp.enabled" Type="Bool">false</Property>
		<Property Name="target.server.tcp.paranoid" Type="Bool">true</Property>
		<Property Name="target.server.tcp.port" Type="Int">3363</Property>
		<Property Name="target.server.tcp.serviceName" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.tcp.serviceName.default" Type="Str">Main Application Instance/VI Server</Property>
		<Property Name="target.server.vi.access" Type="Str">+*</Property>
		<Property Name="target.server.vi.callsEnabled" Type="Bool">true</Property>
		<Property Name="target.server.vi.propertiesEnabled" Type="Bool">true</Property>
		<Property Name="target.WebServer.Config" Type="Str">Listen 8000

NI.ServerName default
DocumentRoot "$LVSERVER_DOCROOT"
TypesConfig "$LVSERVER_CONFIGROOT/mime.types"
DirectoryIndex index.htm
WorkerLimit 10
InactivityTimeout 60

LoadModulePath "$LVSERVER_MODULEPATHS"
LoadModule LVAuth lvauthmodule
LoadModule LVRFP lvrfpmodule

#
# Pipeline Definition
#

SetConnector netConnector

AddHandler LVAuth
AddHandler LVRFP

AddHandler fileHandler ""

AddOutputFilter chunkFilter


</Property>
		<Property Name="target.WebServer.Enabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogEnabled" Type="Bool">false</Property>
		<Property Name="target.WebServer.LogPath" Type="Path">/c/ni-rt/system/www/www.log</Property>
		<Property Name="target.WebServer.Port" Type="Int">80</Property>
		<Property Name="target.WebServer.RootPath" Type="Path">/c/ni-rt/system/www</Property>
		<Property Name="target.WebServer.TcpAccess" Type="Str">c+*</Property>
		<Property Name="target.WebServer.Timeout" Type="Int">60</Property>
		<Property Name="target.WebServer.ViAccess" Type="Str">+*</Property>
		<Property Name="target.webservices.SecurityAPIKey" Type="Str">PqVr/ifkAQh+lVrdPIykXlFvg12GhhQFR8H9cUhphgg=:pTe9HRlQuMfJxAG6QCGq7UvoUpJzAzWGKy5SbZ+roSU=</Property>
		<Property Name="target.webservices.ValidTimestampWindow" Type="Int">15</Property>
		<Item Name="Config" Type="Folder">
			<Item Name="SubVI" Type="Folder">
				<Item Name="Get Route Group Specifications.vi" Type="VI" URL="../Config/SubVIs/Get Route Group Specifications.vi"/>
				<Item Name="Remove Group IVI Devices.vi" Type="VI" URL="../Config/SubVIs/Remove Group IVI Devices.vi"/>
			</Item>
			<Item Name="Chad_Test.csv" Type="Document" URL="../Config/Chad_Test.csv"/>
			<Item Name="Create Route File.vi" Type="VI" URL="../Config/Create Route File.vi"/>
		</Item>
		<Item Name="Utility" Type="Folder">
			<Item Name="Find Specification Match.vi" Type="VI" URL="../Utility/Find Specification Match.vi"/>
			<Item Name="Get Switch Device Names.vi" Type="VI" URL="../Utility/Get Switch Device Names.vi"/>
			<Item Name="LRMS_Switching_Config.vi" Type="VI" URL="../Utility/LRMS_Switching_Config.vi"/>
			<Item Name="NI-SWITCH SwitchBlock Configuration.vi" Type="VI" URL="../Utility/NI-SWITCH SwitchBlock Configuration.vi"/>
			<Item Name="SwitchBlock Arrays.vi" Type="VI" URL="../Utility/SwitchBlock Arrays.vi"/>
		</Item>
		<Item Name="LRMS_Scan_Test.vi" Type="VI" URL="../Main/LRMS_Scan_Test.vi"/>
		<Item Name="Dependencies" Type="Dependencies">
			<Item Name="instr.lib" Type="Folder">
				<Item Name="niModInst Close Installed Devices Session.vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Close Installed Devices Session.vi"/>
				<Item Name="niModInst Get Installed Device Attribute (I32).vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Get Installed Device Attribute (I32).vi"/>
				<Item Name="niModInst Get Installed Device Attribute (poly).vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Get Installed Device Attribute (poly).vi"/>
				<Item Name="niModInst Get Installed Device Attribute (String).vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Get Installed Device Attribute (String).vi"/>
				<Item Name="niModInst Open Installed Devices Session.vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Open Installed Devices Session.vi"/>
				<Item Name="niModInst Set Error.vi" Type="VI" URL="/&lt;instrlib&gt;/niModInst/niModInst Set Error.vi"/>
				<Item Name="niSwitch Close.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Close.vi"/>
				<Item Name="niSwitch Connect Channels (Multiple).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels (Multiple).vi"/>
				<Item Name="niSwitch Connect Channels (Single).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels (Single).vi"/>
				<Item Name="niSwitch Connect Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Connect Channels.vi"/>
				<Item Name="niSwitch Disconnect All Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect All Channels.vi"/>
				<Item Name="niSwitch Disconnect Channels (Multiple).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels (Multiple).vi"/>
				<Item Name="niSwitch Disconnect Channels (Single).vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels (Single).vi"/>
				<Item Name="niSwitch Disconnect Channels.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Disconnect Channels.vi"/>
				<Item Name="niSwitch Initialize With Topology.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Initialize With Topology.vi"/>
				<Item Name="niSwitch IVI Error Converter.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch IVI Error Converter.vi"/>
				<Item Name="niSwitch Topologies.ctl" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Topologies.ctl"/>
				<Item Name="niSwitch Wait For Debounce.vi" Type="VI" URL="/&lt;instrlib&gt;/niSwitch/niSwitch.llb/niSwitch Wait For Debounce.vi"/>
			</Item>
			<Item Name="vi.lib" Type="Folder">
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Close File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Close File+.vi"/>
				<Item Name="compatReadText.vi" Type="VI" URL="/&lt;vilib&gt;/_oldvers/_oldvers.llb/compatReadText.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
				<Item Name="Find First Error.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find First Error.vi"/>
				<Item Name="Find Tag.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Find Tag.vi"/>
				<Item Name="Format Message String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Format Message String.vi"/>
				<Item Name="General Error Handler Core CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler Core CORE.vi"/>
				<Item Name="General Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/General Error Handler.vi"/>
				<Item Name="Get String Text Bounds.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Get String Text Bounds.vi"/>
				<Item Name="Get Text Rect.vi" Type="VI" URL="/&lt;vilib&gt;/picture/picture.llb/Get Text Rect.vi"/>
				<Item Name="GetHelpDir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetHelpDir.vi"/>
				<Item Name="GetRTHostConnectedProp.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/GetRTHostConnectedProp.vi"/>
				<Item Name="Longest Line Length in Pixels.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Longest Line Length in Pixels.vi"/>
				<Item Name="LVBoundsTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVBoundsTypeDef.ctl"/>
				<Item Name="LVRectTypeDef.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/miscctls.llb/LVRectTypeDef.ctl"/>
				<Item Name="niseBus Get Channel Pairs.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseBus Get Channel Pairs.vi"/>
				<Item Name="niseBus Get Hardwires.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseBus Get Hardwires.vi"/>
				<Item Name="niseCfg Close Configuration.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Close Configuration.vi"/>
				<Item Name="niseCfg Close Object.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Close Object.vi"/>
				<Item Name="niseCfg Get Object.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Get Object.vi"/>
				<Item Name="niseCfg Get Objects.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Get Objects.vi"/>
				<Item Name="niseCfg Get Virtual Device.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Get Virtual Device.vi"/>
				<Item Name="niseCfg Get Virtual Devices.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Get Virtual Devices.vi"/>
				<Item Name="niseCfg Open Configuration.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseCfg Open Configuration.vi"/>
				<Item Name="niseExclusion Get Mutual Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseExclusion Get Mutual Channels.vi"/>
				<Item Name="niseExclusion Get Set Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseExclusion Get Set Channels.vi"/>
				<Item Name="niseHardwire Get Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseHardwire Get Channels.vi"/>
				<Item Name="niseIviDevice Get Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseIviDevice Get Channels.vi"/>
				<Item Name="niseRoute Get Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseRoute Get Channels.vi"/>
				<Item Name="niseRoute Get Route Groups.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseRoute Get Route Groups.vi"/>
				<Item Name="niseRouteGroup Get Route Groups.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseRouteGroup Get Route Groups.vi"/>
				<Item Name="niseRouteGroup Get Routes.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseRouteGroup Get Routes.vi"/>
				<Item Name="niseVirtualDevice Get Bus.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Bus.vi"/>
				<Item Name="niseVirtualDevice Get Buses.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Buses.vi"/>
				<Item Name="niseVirtualDevice Get Channel.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Channel.vi"/>
				<Item Name="niseVirtualDevice Get Channels.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Channels.vi"/>
				<Item Name="niseVirtualDevice Get Exclusion.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Exclusion.vi"/>
				<Item Name="niseVirtualDevice Get Exclusions.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Exclusions.vi"/>
				<Item Name="niseVirtualDevice Get Hardwire.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Hardwire.vi"/>
				<Item Name="niseVirtualDevice Get Hardwires.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Hardwires.vi"/>
				<Item Name="niseVirtualDevice Get IVI Device.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get IVI Device.vi"/>
				<Item Name="niseVirtualDevice Get IVI Devices.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get IVI Devices.vi"/>
				<Item Name="niseVirtualDevice Get Route Group.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Route Group.vi"/>
				<Item Name="niseVirtualDevice Get Route Groups.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Route Groups.vi"/>
				<Item Name="niseVirtualDevice Get Route.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Route.vi"/>
				<Item Name="niseVirtualDevice Get Routes.vi" Type="VI" URL="/&lt;vilib&gt;/SwitchExecutive/niseCfg.llb/niseVirtualDevice Get Routes.vi"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Open File+.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Open File+.vi"/>
				<Item Name="Read Delimited Spreadsheet (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Delimited Spreadsheet (DBL).vi"/>
				<Item Name="Read Delimited Spreadsheet (I64).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Delimited Spreadsheet (I64).vi"/>
				<Item Name="Read Delimited Spreadsheet (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Delimited Spreadsheet (string).vi"/>
				<Item Name="Read Delimited Spreadsheet.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Delimited Spreadsheet.vi"/>
				<Item Name="Read File+ (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read File+ (string).vi"/>
				<Item Name="Read Lines From File (with error IO).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Read Lines From File (with error IO).vi"/>
				<Item Name="Remove Duplicates From 1D Array.vim" Type="VI" URL="/&lt;vilib&gt;/Array/Remove Duplicates From 1D Array.vim"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
				<Item Name="Write Delimited Spreadsheet (DBL).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (DBL).vi"/>
				<Item Name="Write Delimited Spreadsheet (I64).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (I64).vi"/>
				<Item Name="Write Delimited Spreadsheet (string).vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet (string).vi"/>
				<Item Name="Write Delimited Spreadsheet.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Delimited Spreadsheet.vi"/>
				<Item Name="Write Spreadsheet String.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Write Spreadsheet String.vi"/>
			</Item>
			<Item Name="nilvaiu.dll" Type="Document" URL="nilvaiu.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="niModInst.dll" Type="Document" URL="niModInst.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="niswitch_32.dll" Type="Document" URL="niswitch_32.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
