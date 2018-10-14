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
                <FileData Type="Normal" Path="cont/adui10_2.png" Plist="" />
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
                <FileData Type="Normal" Path="cont/adui35.png" Plist="" />
                <BlendFunc Src="1" Dst="771" />
              </AbstractNodeData>
            </Children>
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="182.1176" Y="161.8839" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.1603" Y="0.2529" />
            <PreSize X="0.4930" Y="0.8750" />
            <FileData Type="Normal" Path="cont/adui10.png" Plist="" />
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
            <FileData Type="Normal" Path="cont/joyk2.png" Plist="" />
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
            <PressedFileData Type="Normal" Path="cont/icon2_1.png" Plist="" />
            <NormalFileData Type="Normal" Path="cont/icon2_2.png" Plist="" />
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
            <NormalFileData Type="Normal" Path="cont/atk_but.png" Plist="" />
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
          <AbstractNodeData Name="Button_Skill1" ActionTag="946138627" CallBackType="Click" CallBackName="onClickSkill" UserData="1" Tag="41" IconVisible="False" LeftMargin="812.5917" RightMargin="253.4083" TopMargin="521.0684" BottomMargin="48.9316" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="40" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="70.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="847.5917" Y="83.9316" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7461" Y="0.1311" />
            <PreSize X="0.0616" Y="0.1094" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="cont/taidaoay01.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_Skill2" ActionTag="-1079691799" CallBackType="Click" CallBackName="onClickSkill" UserData="2" Tag="42" IconVisible="False" LeftMargin="845.0519" RightMargin="220.9481" TopMargin="404.5803" BottomMargin="165.4197" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="40" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="70.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="880.0519" Y="200.4197" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.7747" Y="0.3132" />
            <PreSize X="0.0616" Y="0.1094" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="cont/taidaoay01.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_Skill3" ActionTag="-1154577288" CallBackType="Click" CallBackName="onClickSkill" UserData="3" Tag="43" IconVisible="False" LeftMargin="934.2545" RightMargin="131.7455" TopMargin="343.6519" BottomMargin="226.3481" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="40" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="70.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="969.2545" Y="261.3481" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.8532" Y="0.4084" />
            <PreSize X="0.0616" Y="0.1094" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="cont/taidaoay01.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="Button_Skill4" ActionTag="1849018291" CallBackType="Click" CallBackName="onClickSkill" UserData="4" Tag="44" IconVisible="False" LeftMargin="1043.5527" RightMargin="22.4473" TopMargin="339.4669" BottomMargin="230.5331" TouchEnable="True" FontSize="14" ButtonText="Button" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="40" Scale9Height="48" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="70.0000" Y="70.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="1078.5527" Y="265.5331" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.9494" Y="0.4149" />
            <PreSize X="0.0616" Y="0.1094" />
            <TextColor A="255" R="65" G="65" B="70" />
            <NormalFileData Type="Normal" Path="cont/taidaoay01.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>