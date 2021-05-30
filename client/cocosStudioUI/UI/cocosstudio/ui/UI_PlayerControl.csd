<GameFile>
  <PropertyGroup Name="playerControlUI" Type="Scene" ID="018d0ec6-6a6d-4c7c-ba8d-409354267e4c" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Scene" Tag="232" ctype="GameNodeObjectData">
        <Size X="1136.0000" Y="640.0000" />
        <Children>
          <AbstractNodeData Name="sprite_BG" ActionTag="-1793560085" Tag="234" IconVisible="False" LeftMargin="-97.8824" RightMargin="673.8824" TopMargin="198.1161" BottomMargin="-118.1161" ctype="SpriteObjectData">
            <Size X="560.0000" Y="560.0000" />
            <Children>
              <AbstractNodeData Name="sprite_Ori" ActionTag="-37246561" Tag="235" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="169.5000" RightMargin="169.5000" TopMargin="169.5000" BottomMargin="169.5000" ctype="SpriteObjectData">
                <Size X="221.0000" Y="221.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="280.0000" Y="280.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.3946" Y="0.3946" />
                <FileData Type="Normal" Path="plist/cont/adui10_2.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
              <AbstractNodeData Name="sprite_Red" ActionTag="-2110845911" Tag="236" IconVisible="False" PositionPercentXEnabled="True" PositionPercentYEnabled="True" LeftMargin="169.5000" RightMargin="169.5000" TopMargin="169.5000" BottomMargin="169.5000" ctype="SpriteObjectData">
                <Size X="221.0000" Y="221.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position X="280.0000" Y="280.0000" />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition X="0.5000" Y="0.5000" />
                <PreSize X="0.3946" Y="0.3946" />
                <FileData Type="Normal" Path="plist/cont/adui35.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="182.1176" Y="161.8839" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1603" Y="0.2529" />
            <PreSize X="0.4930" Y="0.8750" />
            <FileData Type="Normal" Path="plist/cont/adui10.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="sprite_Move" ActionTag="1583954319" Tag="233" IconVisible="False" LeftMargin="-117.8807" RightMargin="653.8807" TopMargin="178.1142" BottomMargin="-138.1142" ctype="SpriteObjectData">
            <Size X="600.0000" Y="600.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="182.1193" Y="161.8858" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1603" Y="0.2529" />
            <PreSize X="0.5282" Y="0.9375" />
            <FileData Type="Normal" Path="plist/cont/joyk2.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_ChangeWeapon" ActionTag="1467032247" VisibleForFrame="False" CallBackType="Click" CallBackName="onClickChangeWeapon" Tag="249" IconVisible="False" LeftMargin="640.8053" RightMargin="385.1947" TopMargin="496.4332" BottomMargin="33.5668" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="80" Scale9Height="88" DisplayState="False" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="110.0000" Y="110.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="695.8053" Y="88.5668" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.6125" Y="0.1384" />
            <PreSize X="0.0968" Y="0.1719" />
            <TextColor A="255" R="65" G="65" B="70" />
            <PressedFileData Type="Normal" Path="plist/cont/icon2_1.png" Plist="" />
            <NormalFileData Type="Normal" Path="plist/cont/icon2_2.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_1" ActionTag="262148636" CallBackType="Click" CallBackName="onClickAttack" Tag="19" IconVisible="False" LeftMargin="948.3350" RightMargin="57.6650" TopMargin="469.3544" BottomMargin="40.6456" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="100" Scale9Height="108" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="130.0000" Y="130.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1013.3350" Y="105.6456" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8920" Y="0.1651" />
            <PreSize X="0.1144" Y="0.2031" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="plist/cont/atk_but.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_2" ActionTag="-1790558230" CallBackType="Click" CallBackName="onClickOpenDebug" Tag="68" IconVisible="False" LeftMargin="48.5382" RightMargin="1015.9161" TopMargin="35.7249" BottomMargin="563.1660" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="16" Scale9Height="14" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="71.5457" Y="41.1091" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="84.3111" Y="583.7205" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0742" Y="0.9121" />
            <PreSize X="0.0630" Y="0.0642" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Default" Path="Default/Button_Press.png" Plist="" />
            <NormalFileData Type="Default" Path="Default/Button_Normal.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_Skill_1" ActionTag="260833247" Tag="22" IconVisible="True" LeftMargin="864.7178" RightMargin="271.2822" TopMargin="572.3649" BottomMargin="67.6351" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Image" ActionTag="891076302" Tag="21" IconVisible="False" LeftMargin="-35.0000" RightMargin="-35.0000" TopMargin="-35.5000" BottomMargin="-35.5000" LeftEage="27" RightEage="27" TopEage="27" BottomEage="27" Scale9OriginX="27" Scale9OriginY="27" Scale9Width="16" Scale9Height="17" ctype="ImageViewObjectData">
                <Size X="70.0000" Y="71.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="plist/cont/ay02.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Skill" ActionTag="-1079691799" CallBackType="Click" CallBackName="onClickSkill" UserData="1" Tag="42" IconVisible="False" LeftMargin="-42.0000" RightMargin="-42.0000" TopMargin="-42.0000" BottomMargin="-42.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="54" Scale9Height="62" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="84.0000" Y="84.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="plist/cont/c_but_2.png" Plist="" />
                <NormalFileData Type="Normal" Path="plist/cont/c_but_1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="864.7178" Y="67.6351" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7612" Y="0.1057" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_Skill_2" ActionTag="1698137021" Tag="23" IconVisible="True" LeftMargin="895.5136" RightMargin="240.4864" TopMargin="472.3197" BottomMargin="167.6803" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Image" ActionTag="-1585382867" Tag="24" IconVisible="False" LeftMargin="-35.5000" RightMargin="-35.5000" TopMargin="-35.5000" BottomMargin="-35.5000" LeftEage="27" RightEage="27" TopEage="27" BottomEage="27" Scale9OriginX="27" Scale9OriginY="27" Scale9Width="17" Scale9Height="17" ctype="ImageViewObjectData">
                <Size X="71.0000" Y="71.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="plist/cont/xiazhan.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Skill" ActionTag="-105784441" CallBackType="Click" CallBackName="onClickSkill" UserData="2" Tag="25" IconVisible="False" LeftMargin="-42.0000" RightMargin="-42.0000" TopMargin="-42.0000" BottomMargin="-42.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="54" Scale9Height="62" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="84.0000" Y="84.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="plist/cont/c_but_2.png" Plist="" />
                <NormalFileData Type="Normal" Path="plist/cont/c_but_1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="895.5136" Y="167.6803" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7883" Y="0.2620" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_Skill_3" ActionTag="-771537104" Tag="26" IconVisible="True" LeftMargin="1068.4177" RightMargin="67.5823" TopMargin="365.3433" BottomMargin="274.6567" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Image" ActionTag="1292792554" Tag="27" IconVisible="False" LeftMargin="-35.5000" RightMargin="-35.5000" TopMargin="-35.5000" BottomMargin="-35.5000" LeftEage="27" RightEage="27" TopEage="27" BottomEage="27" Scale9OriginX="27" Scale9OriginY="27" Scale9Width="17" Scale9Height="17" ctype="ImageViewObjectData">
                <Size X="71.0000" Y="71.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="plist/cont/xulizhan.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Skill" ActionTag="2126499687" CallBackType="Click" CallBackName="onClickSkill" UserData="4" Tag="28" IconVisible="False" LeftMargin="-42.0000" RightMargin="-42.0000" TopMargin="-42.0000" BottomMargin="-42.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="54" Scale9Height="62" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="84.0000" Y="84.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="plist/cont/c_but_2.png" Plist="" />
                <NormalFileData Type="Normal" Path="plist/cont/c_but_1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="1068.4177" Y="274.6567" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9405" Y="0.4292" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
          <AbstractNodeData Name="Node_Skill_4" ActionTag="-909560755" Tag="29" IconVisible="True" LeftMargin="970.9692" RightMargin="165.0308" TopMargin="401.3378" BottomMargin="238.6622" ctype="SingleNodeObjectData">
            <Size X="0.0000" Y="0.0000" />
            <Children>
              <AbstractNodeData Name="Image" ActionTag="-1390479551" Tag="30" IconVisible="False" LeftMargin="-35.0000" RightMargin="-35.0000" TopMargin="-35.5000" BottomMargin="-35.5000" LeftEage="27" RightEage="27" TopEage="27" BottomEage="27" Scale9OriginX="27" Scale9OriginY="27" Scale9Width="16" Scale9Height="17" ctype="ImageViewObjectData">
                <Size X="70.0000" Y="71.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <FileData Type="Normal" Path="plist/cont/ay01.png" Plist="" />
              </AbstractNodeData>
              <AbstractNodeData Name="Button_Skill" ActionTag="93598929" CallBackType="Click" CallBackName="onClickSkill" UserData="3" Tag="31" IconVisible="False" LeftMargin="-42.0000" RightMargin="-42.0000" TopMargin="-42.0000" BottomMargin="-42.0000" TouchEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="54" Scale9Height="62" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
                <Size X="84.0000" Y="84.0000" />
                <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
                <Position />
                <Scale ScaleX="1.0000" ScaleY="1.0000" />
                <CColor A="255" R="255" G="255" B="255" />
                <PrePosition />
                <PreSize X="0.0000" Y="0.0000" />
                <TextColor A="255" R="65" G="65" B="70" />
                <PressedFileData Type="Normal" Path="plist/cont/c_but_2.png" Plist="" />
                <NormalFileData Type="Normal" Path="plist/cont/c_but_1.png" Plist="" />
                <OutlineColor A="255" R="255" G="0" B="0" />
                <ShadowColor A="255" R="110" G="110" B="110" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint />
            <Position X="970.9692" Y="238.6622" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8547" Y="0.3729" />
            <PreSize X="0.0000" Y="0.0000" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>