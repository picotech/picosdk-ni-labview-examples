<?xml version='1.0' encoding='UTF-8'?>
<Project Type="Project" LVVersion="24008000">
	<Property Name="NI.LV.All.SourceOnly" Type="Bool">true</Property>
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
		<Item Name="ps3000a" Type="Folder" URL="..">
			<Property Name="NI.DISK" Type="Bool">true</Property>
		</Item>
		<Item Name="Dependencies" Type="Dependencies">
			<Property Name="NI.SortType" Type="Int">2</Property>
			<Item Name="vi.lib" Type="Folder">
				<Item Name="Analog to Digital.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DWDT.llb/Analog to Digital.vi"/>
				<Item Name="Application Directory.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Application Directory.vi"/>
				<Item Name="BuildHelpPath.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/BuildHelpPath.vi"/>
				<Item Name="Check Special Tags.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Check Special Tags.vi"/>
				<Item Name="Clear Errors.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Clear Errors.vi"/>
				<Item Name="Convert property node font to graphics font.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Convert property node font to graphics font.vi"/>
				<Item Name="Details Display Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Details Display Dialog.vi"/>
				<Item Name="Dflt Data Dir.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/file.llb/Dflt Data Dir.vi"/>
				<Item Name="DialogType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogType.ctl"/>
				<Item Name="DialogTypeEnum.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/DialogTypeEnum.ctl"/>
				<Item Name="DTbl Analog to Digital.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DTblOps.llb/DTbl Analog to Digital.vi"/>
				<Item Name="DTbl Compress Digital.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DTblOps.llb/DTbl Compress Digital.vi"/>
				<Item Name="DTbl Digital Size.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DTblOps.llb/DTbl Digital Size.vi"/>
				<Item Name="DWDT Analog to Digital.vi" Type="VI" URL="/&lt;vilib&gt;/Waveform/DWDTOps.llb/DWDT Analog to Digital.vi"/>
				<Item Name="Error Cluster From Error Code.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Cluster From Error Code.vi"/>
				<Item Name="Error Code Database.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Error Code Database.vi"/>
				<Item Name="ErrWarn.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/ErrWarn.ctl"/>
				<Item Name="eventvkey.ctl" Type="VI" URL="/&lt;vilib&gt;/event_ctls.llb/eventvkey.ctl"/>
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
				<Item Name="NI_FileType.lvlib" Type="Library" URL="/&lt;vilib&gt;/Utility/lvfile.llb/NI_FileType.lvlib"/>
				<Item Name="Not Found Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Not Found Dialog.vi"/>
				<Item Name="Search and Replace Pattern.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Search and Replace Pattern.vi"/>
				<Item Name="Set Bold Text.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set Bold Text.vi"/>
				<Item Name="Set String Value.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Set String Value.vi"/>
				<Item Name="Simple Error Handler.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Simple Error Handler.vi"/>
				<Item Name="Space Constant.vi" Type="VI" URL="/&lt;vilib&gt;/dlg_ctls.llb/Space Constant.vi"/>
				<Item Name="TagReturnType.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/TagReturnType.ctl"/>
				<Item Name="Three Button Dialog CORE.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog CORE.vi"/>
				<Item Name="Three Button Dialog.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Three Button Dialog.vi"/>
				<Item Name="Trim Whitespace One-Sided.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace One-Sided.vi"/>
				<Item Name="Trim Whitespace.vi" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/Trim Whitespace.vi"/>
				<Item Name="whitespace.ctl" Type="VI" URL="/&lt;vilib&gt;/Utility/error.llb/whitespace.ctl"/>
			</Item>
			<Item Name="Acquisition Settings.ctl" Type="VI" URL="../../shared/Acquisition Settings.ctl"/>
			<Item Name="Buffer and Transfer Settings.ctl" Type="VI" URL="../../shared/Buffer and Transfer Settings.ctl"/>
			<Item Name="CreateBuffer.vi" Type="VI" URL="../../shared/CreateBuffer.vi"/>
			<Item Name="DataBufferSizes.vi" Type="VI" URL="../../shared/DataBufferSizes.vi"/>
			<Item Name="DebugTestBufferValuesAndLog.vi" Type="VI" URL="../../shared/DebugTestBufferValuesAndLog.vi"/>
			<Item Name="Detect Current LV Bitness.vi" Type="VI" URL="//picotech.co.uk/users$/Homes/andrew.abbott/Home/Documents/LabVIEW_Working/shared/Detect Current LV Bitness.vi"/>
			<Item Name="Detect Current LV Bitness.vi" Type="VI" URL="../../shared/Detect Current LV Bitness.vi"/>
			<Item Name="nSegments.ctl" Type="VI" URL="../../shared/nSegments.ctl"/>
			<Item Name="PICO_STATUS codes.vi" Type="VI" URL="../../shared/PICO_STATUS codes.vi"/>
			<Item Name="PicoBuffers.ctl" Type="VI" URL="../../shared/PicoBuffers.ctl"/>
			<Item Name="PicoCreatePicoMultiBuffers.vi" Type="VI" URL="../../shared/PicoCreatePicoMultiBuffers.vi"/>
			<Item Name="PicoErrorHandler.vi" Type="VI" URL="../../shared/PicoErrorHandler.vi"/>
			<Item Name="PicoErrorHandler.vi" Type="VI" URL="../../../shared/PicoScope.llb/PicoErrorHandler.vi"/>
			<Item Name="PicoErrorHandler2.vi" Type="VI" URL="//picotech.co.uk/users$/Homes/andrew.abbott/Home/Documents/LabVIEW_Working/shared/PicoScope.llb/PicoErrorHandler2.vi"/>
			<Item Name="PicoErrorHandler2.vi" Type="VI" URL="../../shared/PicoErrorHandler2.vi"/>
			<Item Name="PicoErrorString.vi" Type="VI" URL="../../shared/PicoErrorString.vi"/>
			<Item Name="PicoErrorString2.vi" Type="VI" URL="../../shared/PicoErrorString2.vi"/>
			<Item Name="PicoReadPicoMultiBuffers.vi" Type="VI" URL="../../shared/PicoReadPicoMultiBuffers.vi"/>
			<Item Name="PicoReadPicoStreamingBuffers.vi" Type="VI" URL="../../shared/PicoReadPicoStreamingBuffers.vi"/>
			<Item Name="PicoReleaseBuffers.vi" Type="VI" URL="../../shared/PicoReleaseBuffers.vi"/>
			<Item Name="PicoReleaseMultiBuffers.vi" Type="VI" URL="../../shared/PicoReleaseMultiBuffers.vi"/>
			<Item Name="PicoScope3000aAdvancedTriggerSettings.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aAdvancedTriggerSettings.vi"/>
			<Item Name="PicoScope3000aAdvancedTriggerSettingsV2.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aAdvancedTriggerSettingsV2.vi"/>
			<Item Name="PicoScope3000aAnalogChannelSettings.ctl" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aAnalogChannelSettings.ctl"/>
			<Item Name="PicoScope3000aAWG.vi" Type="VI" URL="../PicoScope3000a.llb/PicoScope3000aAWG.vi"/>
			<Item Name="PicoScope3000aClose.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aClose.vi"/>
			<Item Name="PicoScope3000aClose.vi" Type="VI" URL="../PicoScope3000a.llb/PicoScope3000aClose.vi"/>
			<Item Name="PicoScope3000aDigitalChannelSettings.ctl" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aDigitalChannelSettings.ctl"/>
			<Item Name="PicoScope3000aGetBlock.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetBlock.vi"/>
			<Item Name="PicoScope3000aGetEts.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetEts.vi"/>
			<Item Name="PicoScope3000aGetRapidBlock.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetRapidBlock.vi"/>
			<Item Name="PicoScope3000aGetRapidBlockBulk.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetRapidBlockBulk.vi"/>
			<Item Name="PicoScope3000aGetStreamingValues - Copy.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetStreamingValues - Copy.vi"/>
			<Item Name="PicoScope3000aGetStreamingValues.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetStreamingValues.vi"/>
			<Item Name="PicoScope3000aGetTimebase2.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aGetTimebase2.vi"/>
			<Item Name="PicoScope3000aOpen.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aOpen.vi"/>
			<Item Name="PicoScope3000aOpen.vi" Type="VI" URL="../PicoScope3000a.llb/PicoScope3000aOpen.vi"/>
			<Item Name="PicoScope3000aSettings.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aSettings.vi"/>
			<Item Name="PicoScope3000aStartStreaming.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aStartStreaming.vi"/>
			<Item Name="PicoScope3000aWrap.vi" Type="VI" URL="../OLD/PicoScope3000aLib/PicoScope3000aWrap.vi"/>
			<Item Name="PicoScopeAdcToVolts.vi" Type="VI" URL="../shared/PicoScopeAdcToVolts.vi"/>
			<Item Name="PicoScopeAdcToVolts.vi" Type="VI" URL="../../shared/PicoScopeAdcToVolts.vi"/>
			<Item Name="PicoScopeAdcToVolts.vi" Type="VI" URL="../../../../../SDK_Repos/picosdk-ni-labview-examples/shared/PicoScopeAdcToVolts.vi"/>
			<Item Name="PicoScopeVoltsToAdc.vi" Type="VI" URL="../../shared/PicoScopeVoltsToAdc.vi"/>
			<Item Name="PicoStatus.vi" Type="VI" URL="../../../../../../Repos/picosdk-ni-labview-examples/shared/PicoScope.llb/PicoStatus.vi"/>
			<Item Name="PicoStatus.vi" Type="VI" URL="../shared/PicoStatus.vi"/>
			<Item Name="PicoStatus.vi" Type="VI" URL="../../shared/PicoStatus.vi"/>
			<Item Name="PicoStatus.vi" Type="VI" URL="../../../shared/PicoScope.llb/PicoStatus.vi"/>
			<Item Name="PicoStatus2.vi" Type="VI" URL="../../shared/PicoStatus2.vi"/>
			<Item Name="PicoWritePicoMultiBuffers.vi" Type="VI" URL="../../shared/PicoWritePicoMultiBuffers.vi"/>
			<Item Name="plcm3.dll" Type="Document" URL="plcm3.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ProbeInputRangesScaling.ctl" Type="VI" URL="../../shared/ProbeInputRangesScaling.ctl"/>
			<Item Name="ps2000.dll" Type="Document" URL="ps2000.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps2000a.dll" Type="Document" URL="ps2000a.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps3000.dll" Type="Document" URL="ps3000.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps3000a.dll" Type="Document" URL="ps3000a.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps3000aWrap.dll" Type="Document" URL="ps3000aWrap.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps4000.dll" Type="Document" URL="ps4000.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps4000a.dll" Type="Document" URL="/../Program Files/Pico Technology/SDK/lib/ps4000a.dll"/>
			<Item Name="ps5000a.dll" Type="Document" URL="ps5000a.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps6000.dll" Type="Document" URL="ps6000.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ps6000a.dll" Type="Document" URL="ps6000a.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="psospa.dll" Type="Document" URL="psospa.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="ReadBuffer.vi" Type="VI" URL="../../shared/ReadBuffer.vi"/>
			<Item Name="ReleaseBuffer.vi" Type="VI" URL="../../shared/ReleaseBuffer.vi"/>
			<Item Name="Segment Range.ctl" Type="VI" URL="../../shared/Segment Range.ctl"/>
			<Item Name="UsbPT104.dll" Type="Document" URL="UsbPT104.dll">
				<Property Name="NI.PreserveRelativePath" Type="Bool">true</Property>
			</Item>
			<Item Name="VoltsAmpsVectors_3Phase.vi" Type="VI" URL="../../picosdk-ni-labview-shared-master/VoltsAmpsVectors_3Phase.vi"/>
			<Item Name="WriteBuffer.vi" Type="VI" URL="../../shared/WriteBuffer.vi"/>
		</Item>
		<Item Name="Build Specifications" Type="Build"/>
	</Item>
</Project>
