object Form1: TForm1
  Left = 206
  Top = 0
  BorderIcons = [biSystemMenu, biMinimize]
  BorderStyle = bsSingle
  Caption = 'RadarGL'
  ClientHeight = 704
  ClientWidth = 1180
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  KeyPreview = True
  OldCreateOrder = False
  Position = poScreenCenter
  Scaled = False
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  OnKeyPress = FormKeyPress
  OnMouseWheel = FormMouseWheel
  PixelsPerInch = 96
  TextHeight = 13
  object RzPageControl1: TRzPageControl
    Left = 0
    Top = 0
    Width = 1180
    Height = 704
    ActivePage = TabSheet1
    Align = alClient
    BackgroundColor = clBtnFace
    UseColoredTabs = True
    ParentBackgroundColor = False
    ParentColor = False
    TabIndex = 0
    TabOrder = 0
    FixedDimension = 19
    object TabSheet1: TRzTabSheet
      Caption = #1056#1072#1076#1072#1088
      object RzPanel1: TRzPanel
        Left = 0
        Top = 24
        Width = 654
        Height = 654
        BorderOuter = fsNone
        BorderColor = clBlack
        BorderHighlight = clBlack
        BorderShadow = clBlack
        Color = clBlack
        DoubleBuffered = False
        FullRepaint = False
        Locked = True
        ParentDoubleBuffered = False
        ParentShowHint = False
        ShowHint = False
        TabOrder = 0
        Transparent = True
        OnClick = RzPanel1Click
        OnMouseDown = RzPanel1MouseDown
        OnMouseMove = RzPanel1MouseMove
        OnMouseUp = RzPanel1MouseUp
        OnPaint = RzPanel1Paint
      end
      object RzPanel2: TRzPanel
        Left = 660
        Top = 19
        Width = 605
        Height = 659
        BorderOuter = fsNone
        Color = cl3DLight
        TabOrder = 1
        object rzgrpbx_target: TRzGroupBox
          Left = 0
          Top = 0
          Width = 244
          Height = 921
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1094#1077#1083#1080':'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          FlatColor = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GradientColorStart = clGrayText
          GradientColorStop = clGrayText
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 0
          VisualStyle = vsGradient
          object lbl_epr: TRzLabel
            Left = 33
            Top = 32
            Width = 76
            Height = 13
            Caption = #1069#1055#1056' '#1094#1077#1083#1080' '#1084'.'#1082#1074'.'
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
            BorderColor = clActiveCaption
          end
          object lbl_speed: TRzLabel
            Left = 33
            Top = 55
            Width = 104
            Height = 13
            Caption = #1057#1082#1086#1088#1086#1089#1090#1100' '#1094#1077#1083#1080', '#1082#1084'/'#1095
            Font.Charset = RUSSIAN_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = []
            ParentFont = False
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object edt_epr: TRzMaskEdit
            Left = 142
            Top = 25
            Width = 83
            Height = 21
            AutoSelect = False
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Text = '100'
          end
          object edt_speed: TRzMaskEdit
            Left = 142
            Top = 52
            Width = 80
            Height = 21
            EditMask = '#####;0; '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            TabOrder = 1
            Text = '1080'
          end
        end
        object rzgrpbx_coord3: TRzGroupBox
          Left = 6
          Top = 346
          Width = 244
          Height = 89
          Caption = #1050#1086#1085#1077#1095#1085#1099#1077' '#1082#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1094#1077#1083#1080':'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 3
          VisualStyle = vsGradient
          object lbl_beta3: TRzLabel
            Left = 27
            Top = 32
            Width = 106
            Height = 13
            Caption = #1040#1079#1080#1084#1091#1090' (0-360) '#1075#1088#1072#1076'.'
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object lbl_D3: TRzLabel
            Left = 27
            Top = 58
            Width = 109
            Height = 13
            Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' (0-450) '#1082#1084
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object edt_beta3: TRzMaskEdit
            Left = 136
            Top = 29
            Width = 81
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Text = '90'
          end
          object edt_D3: TRzMaskEdit
            Left = 136
            Top = 55
            Width = 81
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            Text = '50'
          end
        end
        object rzgrpbx_coord0: TRzGroupBox
          Left = 4
          Top = 79
          Width = 244
          Height = 82
          Caption = #1053#1072#1095#1072#1083#1100#1085#1099#1077' '#1082#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1094#1077#1083#1080':'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 1
          VisualStyle = vsGradient
          object lbl_beta0: TRzLabel
            Left = 27
            Top = 32
            Width = 106
            Height = 13
            Caption = #1040#1079#1080#1084#1091#1090' (0-360) '#1075#1088#1072#1076'.'
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object lbl_D0: TRzLabel
            Left = 27
            Top = 58
            Width = 109
            Height = 13
            Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' (0-450) '#1082#1084
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object edt_beta0: TRzMaskEdit
            Left = 139
            Top = 31
            Width = 81
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 0
            Text = '0'
          end
          object edt_D0: TRzMaskEdit
            Left = 136
            Top = 55
            Width = 81
            Height = 21
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            ParentFont = False
            TabOrder = 1
            Text = '50'
          end
        end
        object rzgrpbx_coord2: TRzGroupBox
          Left = 6
          Top = 256
          Width = 244
          Height = 89
          Caption = #1055#1088#1086#1084#1077#1078#1091#1090#1086#1095#1085#1099#1077' '#1082#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1094#1077#1083#1080' 2:'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 2
          VisualStyle = vsGradient
          object lbl_beta2: TRzLabel
            Left = 27
            Top = 32
            Width = 106
            Height = 13
            Caption = #1040#1079#1080#1084#1091#1090' (0-360) '#1075#1088#1072#1076'.'
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object lbl_D2: TRzLabel
            Left = 27
            Top = 58
            Width = 109
            Height = 13
            Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' (0-450) '#1082#1084
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object edt_beta2: TRzMaskEdit
            Left = 136
            Top = 29
            Width = 81
            Height = 21
            EditMask = '#####;0; '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            TabOrder = 0
          end
          object edt_D2: TRzMaskEdit
            Left = 136
            Top = 55
            Width = 81
            Height = 21
            EditMask = '#####;0; '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            TabOrder = 1
          end
        end
        object RzToolbar1: TRzToolbar
          Left = 0
          Top = 615
          Width = 605
          Height = 44
          Align = alBottom
          AutoStyle = False
          Images = ImageList1
          RowHeight = 40
          ButtonLayout = blGlyphTop
          ButtonWidth = 60
          ButtonHeight = 40
          ShowButtonCaptions = True
          TextOptions = ttoCustom
          BorderColor = clBackground
          BorderInner = fsNone
          BorderOuter = fsNone
          BorderSides = [sdTop]
          BorderWidth = 0
          Color = clGradientInactiveCaption
          TabOrder = 4
          VisualStyle = vsGradient
          ToolbarControls = (
            BtnRoute
            BtnBackground
            BtnRestart
            BtnAddTV
            BtnAddTarget
            BtnPlot
            BtnDebug
            BtnData)
          object BtnBackground: TRzToolButton
            Left = 64
            Top = 2
            Hint = 'Utilities'
            DisabledIndex = 3
            GradientColorStyle = gcsSystem
            Flat = False
            ImageIndex = 2
            Layout = blGlyphTop
            UseToolbarVisualStyle = False
            VisualStyle = vsGradient
            Caption = #1060#1086#1085
            OnClick = BtnBackgroundClick
          end
          object BtnRoute: TRzToolButton
            Left = 4
            Top = 2
            Hint = 'Execute'
            DisabledIndex = 11
            ImageIndex = 10
            Layout = blGlyphTop
            Caption = #1058#1077#1089#1090
            OnClick = BtnRouteClick
          end
          object BtnRestart: TRzToolButton
            Left = 124
            Top = 2
            Hint = 'Refresh'
            DisabledIndex = 13
            ImageIndex = 12
            Layout = blGlyphTop
            Caption = #1056#1077#1089#1090#1072#1088#1090
            OnClick = BtnRestartClick
          end
          object BtnAddTV: TRzToolButton
            Left = 184
            Top = 2
            Hint = 'OK'
            DisabledIndex = 15
            ImageIndex = 14
            Layout = blGlyphTop
            Caption = 'Add TV'
            OnClick = BtnAddTVClick
          end
          object BtnPlot: TRzToolButton
            Left = 306
            Top = 2
            Hint = 'Edit'
            DisabledIndex = 19
            ImageIndex = 18
            Layout = blGlyphTop
            Caption = 'Plot'
          end
          object BtnDebug: TRzToolButton
            Left = 366
            Top = 2
            Hint = 'Replace'
            DisabledIndex = 21
            ImageIndex = 20
            Layout = blGlyphTop
            Caption = 'Debug'
            OnClick = BtnDebugClick
          end
          object BtnData: TRzToolButton
            Left = 426
            Top = 2
            Hint = 'Note'
            DisabledIndex = 23
            ImageIndex = 22
            Layout = blGlyphTop
            Caption = #1044#1072#1085#1085#1099#1077
            OnClick = BtnDataClick
          end
          object BtnAddTarget: TRzToolButton
            Left = 244
            Top = 2
            Width = 62
            Height = 40
            Hint = 'Attach'
            DisabledIndex = 17
            ImageIndex = 16
            Layout = blGlyphTop
            Caption = 'Add Target'
            OnClick = BtnAddTargetClick
          end
        end
        object Memo1: TMemo
          Left = 263
          Top = 198
          Width = 250
          Height = 411
          ScrollBars = ssVertical
          TabOrder = 5
        end
        object rzgrpbx_radar: TRzGroupBox
          Left = 0
          Top = 428
          Width = 249
          Height = 181
          Caption = #1055#1072#1088#1072#1084#1077#1090#1088#1099' '#1088#1072#1076#1072#1088#1072':'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          FlatColor = clInfoBk
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GradientColorStart = clGrayText
          GradientColorStop = clGrayText
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 6
          VisualStyle = vsGradient
          object RzRadioGroup1: TRzRadioGroup
            Left = 109
            Top = 21
            Width = 132
            Height = 36
            Caption = #1053#1072#1082#1083#1086#1085' '#1051#1063#1052
            Columns = 2
            ItemIndex = 0
            Items.Strings = (
              #1051#1063#1052'+'
              #1051#1063#1052'-')
            ParentColor = True
            TabOrder = 0
          end
          object RzRadioGroup2: TRzRadioGroup
            Left = 0
            Top = 56
            Width = 241
            Height = 41
            Caption = #1056#1077#1078#1080#1084' '#1088#1072#1073#1086#1090#1099' '#1056#1051#1057
            Columns = 3
            ItemIndex = 1
            Items.Strings = (
              '3 '#1086#1073'./'#1084#1080#1085
              '6 '#1086#1073'./'#1084#1080#1085
              '12 '#1086#1073'./'#1084#1080#1085)
            ParentColor = True
            TabOrder = 1
          end
          object RzEditListBox1: TRzEditListBox
            Left = 7
            Top = 103
            Width = 53
            Height = 57
            ItemHeight = 13
            Items.Strings = (
              '1137927'
              '1219685'
              '1313122'
              '1251719')
            TabOrder = 2
          end
          object RzEditListBox2: TRzEditListBox
            Left = 66
            Top = 103
            Width = 53
            Height = 57
            ItemHeight = 13
            Items.Strings = (
              '890987'
              '954391'
              '1027805'
              '1214679')
            TabOrder = 3
          end
          object RzEditListBox3: TRzEditListBox
            Left = 125
            Top = 103
            Width = 54
            Height = 57
            ItemHeight = 13
            Items.Strings = (
              '900998'
              '991098'
              '1101220'
              '4')
            TabOrder = 4
          end
          object RzComboBox1: TRzComboBox
            Left = 0
            Top = 29
            Width = 103
            Height = 21
            AllowEdit = False
            Style = csDropDownList
            TabOrder = 5
            Text = '90K6'
            Items.Strings = (
              '90K6')
            ItemIndex = 0
          end
        end
        object TV: TTreeView
          Left = 266
          Top = 0
          Width = 247
          Height = 192
          AutoExpand = True
          Indent = 19
          TabOrder = 7
          OnClick = TVClick
        end
        object rzgrpbx_coord1: TRzGroupBox
          Left = 6
          Top = 161
          Width = 244
          Height = 89
          Caption = #1055#1088#1086#1084#1077#1078#1091#1090#1086#1095#1085#1099#1077' '#1082#1086#1086#1088#1076#1080#1085#1072#1090#1099' '#1094#1077#1083#1080' 1:'
          CaptionFont.Charset = DEFAULT_CHARSET
          CaptionFont.Color = clWindowText
          CaptionFont.Height = -9
          CaptionFont.Name = 'Tahoma'
          CaptionFont.Style = [fsBold]
          Color = cl3DLight
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clWindowText
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = []
          GroupStyle = gsBanner
          ParentFont = False
          TabOrder = 8
          VisualStyle = vsGradient
          object lbl_beta1: TRzLabel
            Left = 27
            Top = 32
            Width = 106
            Height = 13
            Caption = #1040#1079#1080#1084#1091#1090' (0-360) '#1075#1088#1072#1076'.'
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object lbl_D1: TRzLabel
            Left = 27
            Top = 58
            Width = 109
            Height = 13
            Caption = #1044#1080#1089#1090#1072#1085#1094#1080#1103' (0-450) '#1082#1084
            BlinkIntervalOff = 1000
            BlinkIntervalOn = 1000
          end
          object edt_beta1: TRzMaskEdit
            Left = 136
            Top = 29
            Width = 81
            Height = 21
            EditMask = '#####;0; '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            TabOrder = 0
            OnEnter = edt_beta1Enter
          end
          object edt_D1: TRzMaskEdit
            Left = 136
            Top = 51
            Width = 81
            Height = 21
            EditMask = '#####;0; '
            Font.Charset = DEFAULT_CHARSET
            Font.Color = clWindowText
            Font.Height = -11
            Font.Name = 'Tahoma'
            Font.Style = [fsBold]
            MaxLength = 5
            ParentFont = False
            TabOrder = 1
          end
        end
      end
      object RzStatusBar1: TRzStatusBar
        Left = 0
        Top = 0
        Width = 1176
        Height = 19
        ShowSizeGrip = False
        Align = alTop
        BorderInner = fsNone
        BorderOuter = fsNone
        BorderSides = [sdLeft, sdTop, sdRight, sdBottom]
        BorderWidth = 0
        Color = clInactiveCaption
        DoubleBuffered = True
        FullRepaint = False
        GradientColorStart = clActiveCaption
        GradientColorStop = clActiveCaption
        ParentDoubleBuffered = False
        TabOrder = 2
        object RzMapInfo: TRzFieldStatus
          Left = 355
          Top = 0
          Width = 254
          Height = 19
          FillColor = clSilver
          ParentFillColor = False
          Font.Charset = DEFAULT_CHARSET
          Font.Color = clNavy
          Font.Height = -11
          Font.Name = 'Tahoma'
          Font.Style = [fsBold]
          ParentFont = False
          FieldLabel = #1044#1072#1083#1100#1085#1086#1089#1090#1100' '#1080' '#1072#1079#1080#1084#1091#1090':'
          FieldLabelColor = clGray
          Alignment = taCenter
          BlinkColor = clNavy
          BlinkIntervalOff = 1000
          BlinkIntervalOn = 1000
        end
      end
    end
    object TabSheet2: TRzTabSheet
      Caption = #1043#1088#1072#1092#1080#1082
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 1189
      ExplicitHeight = 0
      object Chart1: TChart
        Left = 0
        Top = 0
        Width = 1176
        Height = 300
        Legend.Visible = False
        Title.Text.Strings = (
          'TChart')
        View3D = False
        Align = alTop
        TabOrder = 0
        ExplicitWidth = 1189
        ColorPaletteIndex = 13
        object Series1: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          LinePen.Color = 10708548
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object Chart2: TChart
        Left = 0
        Top = 300
        Width = 1176
        Height = 300
        Legend.Visible = False
        Title.Text.Strings = (
          'TChart')
        View3D = False
        Align = alTop
        TabOrder = 1
        ExplicitWidth = 1189
        ColorPaletteIndex = 13
        object Series3: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          LinePen.Color = 10708548
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object Chart3: TChart
        Left = 0
        Top = 600
        Width = 1176
        Height = 300
        Legend.Visible = False
        Title.Text.Strings = (
          'TChart')
        Pages.AutoScale = True
        Pages.MaxPointsPerPage = 3000
        View3D = False
        Align = alTop
        TabOrder = 2
        ExplicitWidth = 1189
        ColorPaletteIndex = 13
        object Series2: TLineSeries
          Marks.Arrow.Visible = True
          Marks.Callout.Brush.Color = clBlack
          Marks.Callout.Arrow.Visible = True
          Marks.Visible = False
          LinePen.Color = 10708548
          Pointer.Brush.Gradient.EndColor = 10708548
          Pointer.Gradient.EndColor = 10708548
          Pointer.InflateMargins = True
          Pointer.Style = psRectangle
          Pointer.Visible = False
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
    end
    object TabSheet3: TRzTabSheet
      Caption = #1044#1072#1085#1085#1099#1077
      ExplicitLeft = 0
      ExplicitTop = 0
      ExplicitWidth = 0
      ExplicitHeight = 0
      object Memo2: TMemo
        Left = 0
        Top = 3
        Width = 185
        Height = 929
        ScrollBars = ssVertical
        TabOrder = 0
      end
      object Memo3: TMemo
        Left = 191
        Top = 3
        Width = 185
        Height = 929
        ScrollBars = ssVertical
        TabOrder = 1
      end
      object Memo4: TMemo
        Left = 382
        Top = 3
        Width = 185
        Height = 929
        Lines.Strings = (
          'LFMup'
          '--------')
        ScrollBars = ssVertical
        TabOrder = 2
      end
      object Memo5: TMemo
        Left = 573
        Top = 3
        Width = 185
        Height = 929
        Lines.Strings = (
          'LFMdown'
          '-----------')
        ScrollBars = ssVertical
        TabOrder = 3
      end
      object Memo6: TMemo
        Left = 764
        Top = 3
        Width = 185
        Height = 929
        Lines.Strings = (
          'ArrBig'
          '-------------')
        ScrollBars = ssVertical
        TabOrder = 4
      end
      object Memo7: TMemo
        Left = 955
        Top = 3
        Width = 185
        Height = 929
        ScrollBars = ssVertical
        TabOrder = 5
      end
      object Memo8: TMemo
        Left = 1146
        Top = 3
        Width = 185
        Height = 929
        ScrollBars = ssVertical
        TabOrder = 6
      end
    end
  end
  object ImageList1: TImageList
    Left = 147
    Top = 56
    Bitmap = {
      494C010118001D00600010001000FFFFFFFFFF10FFFFFFFFFFFFFFFF424D3600
      0000000000003600000028000000400000007000000001002000000000000070
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300009933000099330000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900999999009999
      99009999990099999900999999009999990000000000FF990000CC660000CC66
      0000CC660000CC660000CC660000CC660000CC660000CC660000CC6600000000
      00000000000000000000000000000000000000000000CCCCCC00999999009999
      9900999999009999990099999900999999009999990099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC0099999900FF990000CC660000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC66
      000000000000000000000000000000000000CCCCCC0099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF00000080000000000099330000CC66
      0000CC660000CC66000099330000000000000000000000000000000000000000
      0000000000000000000000000000B2B2B200999999000000000099999900CCCC
      CC00CCCCCC00CCCCCC009999990000000000FF990000CC660000E5E5E500E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CC66
      000000000000000000000000000000000000CCCCCC0099999900E5E5E500E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000099000000990000008000000000009933
      0000CC6600009933000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B200999999009999990099999900000000009999
      9900CCCCCC00999999000000000000000000FF990000CC660000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00CC66
      000000000000000000000000000000000000CCCCCC0099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000099000000800000009900000080000000
      0000993300000000000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B200999999009999990099999900999999000000
      000099999900000000000000000000000000FF990000CC660000E5E5E500E5E5
      E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CC66
      000000000000000000000000000000000000CCCCCC0099999900E5E5E500E5E5
      E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000FF00000099000000990000008000000099000000
      8000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000B2B2B200999999009999990099999900999999009999
      990000000000000000000000000000000000FF990000CC660000FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CC66
      000000000000000000000000000000000000CCCCCC0099999900FFFFFF00FFFF
      FF00FFFFFF00FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00CC9966000000990000009900000099000000FF000000
      9900000080000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF0099999900999999009999990099999900B2B2B2009999
      990099999900000000000000000000000000FF990000CC660000E5E5E500E5E5
      E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CC66
      000000000000000000000000000000000000CCCCCC0099999900E5E5E500E5E5
      E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000FFFFFF00FFCC9900FFCC9900000099000000FF000000FF000000
      FF00000099000000800000000000000000000000000000000000000000000000
      000000000000FFFFFF00CCCCCC00CCCCCC0099999900B2B2B200B2B2B200B2B2
      B20099999900999999000000000000000000FF990000CC660000FFFFFF00FFFF
      FF00FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CC66
      000000000000000000000000000000000000CCCCCC0099999900FFFFFF00FFFF
      FF00FFFFFF00E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E5009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000FFFFFF00FFCC9900FFCC9900FFFFFF00FFFFFF000000FF003399FF003399
      FF003399FF000000990000000000000000000000000000000000000000000000
      0000FFFFFF00CCCCCC00CCCCCC00FFFFFF00FFFFFF00B2B2B200CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000FF990000CC660000E5E5E500E5E5
      E500CCCCCC00CCCCCC00CC660000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC660000CC660000CCCCCC0099999900E5E5E500E5E5
      E500CCCCCC00CCCCCC0099999900999999009999990099999900999999009999
      990099999900999999009999990099999900000000000000000000000000FFFF
      FF00FFCC9900FFCC9900FFFFFF00FFFFFF00FFFFFF00FFFFFF00000099000000
      990000009900000000000000000000000000000000000000000000000000FFFF
      FF00CCCCCC00CCCCCC00FFFFFF00FFFFFF00FFFFFF00FFFFFF00999999009999
      990099999900000000000000000000000000FF990000CC660000FFFFFF00FFFF
      FF00E5E5E500CC660000FF990000CC660000CC660000CC660000CC660000CC66
      0000CC660000CC660000CC660000CC660000CCCCCC0099999900FFFFFF00FFFF
      FF00E5E5E50099999900CCCCCC00999999009999990099999900999999009999
      9900999999009999990099999900999999000000000000000000FFFFFF00FFCC
      9900FFCC9900FFFFFF00FFFFFF00FFFFFF00CC996600CC996600000000000000
      0000000000000000000000000000000000000000000000000000FFFFFF00CCCC
      CC00CCCCCC00FFFFFF00FFFFFF00FFFFFF009999990099999900000000000000
      000000000000000000000000000000000000FF990000CC660000E5E5E500CCCC
      CC00FF990000FF990000FF990000FF990000FF990000CC660000CC660000CC66
      0000CC660000CC660000CC66000000000000CCCCCC0099999900E5E5E500CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC0099999900999999009999
      99009999990099999900999999000000000000000000FFFFFF00FFCC9900FFCC
      9900FFFFFF00FFFFFF00FFFFFF00CC9966000000000000000000000000000000
      00000000000000000000000000000000000000000000FFFFFF00CCCCCC00CCCC
      CC00FFFFFF00FFFFFF00FFFFFF00999999000000000000000000000000000000
      000000000000000000000000000000000000FF990000CC660000FFFFFF00FF99
      0000FF996600FF996600FF990000FF990000FF990000FF990000FF990000CC66
      0000CC660000CC6600000000000000000000CCCCCC0099999900FFFFFF00CCCC
      CC00E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      990099999900999999000000000000000000FFFFFF00FFCC9900FFCC9900FFFF
      FF00FFFFFF00FFFFFF00CC9966000000FF000000000000000000000000000000
      000000000000000000000000000000000000FFFFFF00CCCCCC00CCCCCC00FFFF
      FF00FFFFFF00FFFFFF0099999900B2B2B2000000000000000000000000000000
      000000000000000000000000000000000000FF990000CC660000FF990000FF99
      6600FF996600FF996600FF996600FF996600FF990000FF990000FF990000FF99
      0000CC660000000000000000000000000000CCCCCC0099999900CCCCCC00E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCC
      CC0099999900000000000000000000000000CC996600FFCC9900FFFFFF00FFFF
      FF00FFFFFF00CC9966000000FF00000000000000000000000000000000000000
      00000000000000000000000000000000000099999900CCCCCC00FFFFFF00FFFF
      FF00FFFFFF0099999900B2B2B200000000000000000000000000000000000000
      000000000000000000000000000000000000FF990000FF990000FF996600FF99
      6600FF996600FF996600FF996600FF996600FF996600FF996600FF990000CC66
      000000000000000000000000000000000000CCCCCC00CCCCCC00E5E5E500E5E5
      E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500E5E5E500CCCCCC009999
      99000000000000000000000000000000000000000000CC996600FFFFFF00FFFF
      FF00CC9966000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900FFFFFF00FFFF
      FF00999999000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000FF99000099999900FFFF
      FF0099999900FFFFFF0099999900FFFFFF0099999900FFFFFF0099999900FFFF
      FF000000000000000000000000000000000000000000CCCCCC0099999900FFFF
      FF0099999900FFFFFF0099999900FFFFFF0099999900FFFFFF0099999900FFFF
      FF00000000000000000000000000000000000000000000000000CC996600CC99
      6600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC0099999900CCCCCC0099999900CCCCCC0099999900CCCCCC00999999000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC0099999900CCCCCC0099999900CCCCCC0099999900CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000033333300000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000006666660099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00666666000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000CCCCCC00666666000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000003333330066666600666666006666
      6600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009999990066666600666666006666
      6600000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CCCCCC006666
      66000000000000000000FF990000993300009933000099330000000000000000
      0000000000000000000000000000000000000000000000000000CCCCCC006666
      66000000000000000000CCCCCC00666666006666660066666600000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC009999
      9900666666006666660000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC009999
      9900666666006666660000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC0066666600FF990000CC660000CC660000CC660000CC660000993300000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC0066666600CCCCCC0099999900999999009999990099999900666666000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990066666600666666000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00999999009999990066666600666666000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000FF990000CC660000FF990000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CCCCCC0099999900CCCCCC00999999009999990099999900666666000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC009999990099999900999999006666660066666600000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC009999990099999900999999006666660066666600000000000000
      000000000000000000000000000000000000000000000000000000000000FF99
      0000CC660000FF990000FF990000FF990000CC660000CC660000993300000000
      000000000000000000000000000000000000000000000000000000000000CCCC
      CC0099999900CCCCCC00CCCCCC00CCCCCC009999990099999900666666000000
      000000000000000000000000000000000000000000000000000099999900E5E5
      E500CCCCCC00CCCCCC0099999900999999009999990099330000663300006633
      000000000000000000000000000000000000000000000000000099999900E5E5
      E500CCCCCC00CCCCCC0099999900999999009999990099999900666666006666
      660000000000000000000000000000000000000000000000000000000000CC66
      0000FF996600FF996600FF990000FF990000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00CCCCCC00CCCCCC009999990099999900666666000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900E5E5E500CCCCCC00CCCCCC00999999009933000099330000993300009933
      0000663300000000000000000000000000000000000000000000000000009999
      9900E5E5E500CCCCCC00CCCCCC00999999009999990099999900999999009999
      990066666600000000000000000000000000000000000000000000000000CC66
      0000FFFFFF00FFFFFF00FF996600CC660000FF990000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000009999
      9900FFFFFF00FFFFFF00CCCCCC0099999900CCCCCC0099999900999999006666
      6600000000000000000000000000000000000000000000000000000000009999
      9900FFFFFF00E5E5E500CCCCCC00993300009933000099330000993300009933
      0000993300006633000000000000000000000000000000000000000000009999
      9900FFFFFF00E5E5E500CCCCCC00999999009999990099999900999999009999
      990099999900666666000000000000000000000000000000000000000000CC66
      0000FF996600FF996600CC660000FFFFFF00FF996600FF990000CC6600009933
      0000993300009933000099330000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900FFFFFF00CCCCCC00CCCCCC00999999006666
      6600666666006666660066666600000000000000000000000000000000000000
      000099999900FFFFFF0099330000CC6633009933000099330000993300009933
      0000993300009933000066330000000000000000000000000000000000000000
      000099999900FFFFFF0099999900CCCCCC009999990099999900999999009999
      9900999999009999990066666600000000000000000000000000000000000000
      0000CC660000CC660000CC660000CC660000FFFFFF00FF99660099330000CC66
      0000CC660000CC660000CC660000993300000000000000000000000000000000
      000099999900999999009999990099999900FFFFFF00CCCCCC00666666009999
      9900999999009999990099999900666666000000000000000000000000000000
      00009999990099330000CC66330099330000CC66330099330000993300009933
      0000993300009933000099330000663300000000000000000000000000000000
      00009999990099999900CCCCCC0099999900CCCCCC0099999900999999009999
      9900999999009999990099999900666666000000000000000000000000000000
      000000000000000000000000000000000000CC660000CC660000CC660000FF99
      0000CC660000CC660000CC660000993300000000000000000000000000000000
      000000000000000000000000000000000000999999009999990099999900CCCC
      CC00999999009999990099999900666666000000000000000000000000000000
      0000000000009933000099330000CC66330099330000CC663300993300009933
      0000993300009933000099330000993300000000000000000000000000000000
      0000000000009999990099999900CCCCCC0099999900CCCCCC00999999009999
      9900999999009999990099999900999999000000000000000000000000000000
      00000000000000000000000000000000000000000000CC660000FF996600FF99
      0000FF990000CC660000CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990099999900666666000000000000000000000000000000
      000000000000993300009933000099330000CC66330099330000CC6633009933
      0000993300009933000099330000999999000000000000000000000000000000
      000000000000999999009999990099999900CCCCCC0099999900CCCCCC009999
      9900999999009999990099999900999999000000000000000000000000000000
      00000000000000000000000000000000000000000000CC660000FF996600FF99
      6600FF990000CC660000CC660000FF9900000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990099999900CCCCCC000000000000000000000000000000
      00000000000000000000993300009933000099330000CC66330099330000CC66
      3300993300009933000099999900999999000000000000000000000000000000
      00000000000000000000999999009999990099999900CCCCCC0099999900CCCC
      CC00999999009999990099999900999999000000000000000000000000000000
      00000000000000000000000000000000000000000000CC660000FFFFFF00FF99
      6600CC660000CC660000FF990000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900FFFFFF00CCCC
      CC009999990099999900CCCCCC00000000000000000000000000000000000000
      0000000000000000000000000000993300009933000099330000CC6633009933
      000099330000CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000999999009999990099999900CCCCCC009999
      990099999900CCCCCC00CCCCCC00999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000CC660000CC66
      0000CC660000FF99000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000999999009999
      990099999900CCCCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000009933000099330000993300009933
      0000E5E5E500E5E5E500CCCCCC00CCCCCC000000000000000000000000000000
      0000000000000000000000000000000000009999990099999900999999009999
      9900E5E5E500E5E5E500CCCCCC00CCCCCC000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CC9966009933000099330000CC9966000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2009999990099999900B2B2B2000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000CC00000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      000099330000CC660000CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      990099999900CCCCCC00CCCCCC00999999000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      0000009900000099000000660000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200999999009999990080808000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC6600009933000099330000CC9966000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC009999990099999900B2B2B2000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CC00000099
      0000009900000099000000990000006600000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B2B2B2009999
      9900999999009999990099999900808080000000000000000000000000000000
      00000000000000000000000000000000000000000000CC99660099330000CC66
      000099330000CC99660000000000000000009933000099330000993300009933
      00009933000099330000993300000000000000000000B2B2B20099999900CCCC
      CC0099999900B2B2B20000000000000000009999990099999900999999009999
      9900999999009999990099999900000000000000000000CC0000009900000099
      0000009900000099000000990000009900000066000000000000000000000000
      00000000000000000000000000000000000000000000B2B2B200999999009999
      9900999999009999990099999900999999008080800000000000000000000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      0000CC99660000000000000000000000000099330000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900B2B2B20000000000000000000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000CC0000009900000099
      00000066000000CC000000990000009900000099000000660000000000000000
      00000000000000000000000000000000000000000000B2B2B200999999009999
      990080808000B2B2B20099999900999999009999990080808000000000000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000CC0000009900000066
      0000000000000000000000CC0000009900000099000000990000006600000000
      00000000000000000000000000000000000000000000B2B2B200999999008080
      80000000000000000000B2B2B200999999009999990099999900808080000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      0000CC99660000000000000000000000000000000000CC99660099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900B2B2B20000000000000000000000000000000000B2B2B20099999900CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000CC0000006600000000
      000000000000000000000000000000CC00000099000000990000009900000066
      00000000000000000000000000000000000000000000B2B2B200808080000000
      0000000000000000000000000000B2B2B2009999990099999900999999008080
      80000000000000000000000000000000000000000000CC99660099330000CC66
      000099330000CC99660000000000CC9966009933000099330000CC6600009933
      0000CC660000CC660000993300000000000000000000B2B2B20099999900CCCC
      CC0099999900B2B2B20000000000B2B2B2009999990099999900CCCCCC009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000000000000000000000CC000000990000009900000099
      0000006600000000000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000B2B2B20099999900999999009999
      990080808000000000000000000000000000000000000000000099330000CC66
      0000CC660000993300009933000099330000CC660000CC66000099330000CC99
      660099330000CC6600009933000000000000000000000000000099999900CCCC
      CC00CCCCCC00999999009999990099999900CCCCCC00CCCCCC0099999900B2B2
      B20099999900CCCCCC0099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000CC0000009900000099
      0000009900000066000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000B2B2B200999999009999
      9900999999008080800000000000000000000000000000000000000000009933
      000099330000CC660000CC660000CC6600009933000099330000000000000000
      0000000000009933000099330000000000000000000000000000000000009999
      990099999900CCCCCC00CCCCCC00CCCCCC009999990099999900000000000000
      0000000000009999990099999900000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000CC00000099
      0000009900000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000B2B2B2009999
      9900999999008080800000000000000000000000000000000000000000000000
      0000CC996600993300009933000099330000CC99660000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200999999009999990099999900B2B2B20000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000000000000000000000000000000CC
      0000009900000066000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000000000000B2B2
      B200999999008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000000CC00000066000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2008080800000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC000099CC00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066CCCC000099CC000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300000000000000000000000000000000000000000000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000066CCCC0099FFFF000099CC0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900E5E5E5009999990000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000066CCCC000099CC000099CC000099CC0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900999999009999990099999900CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      000099330000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      000066CCCC0099FFFF0066FFFF0066FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0066FFFF000099CC0066CCCC0066CCCC0066CC
      CC00000000000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500CCCCCC009999990099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      000099330000CC660000CC660000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0066FFFF0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099330000CC660000CC660000CC66000099330000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC00CCCCCC00CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000066CCCC000099
      CC000099CC000099CC000099CC0099FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900E5E5E500CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099330000CC660000CC660000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      000000000000000000000000000000000000000000000000000066CCCC0099FF
      FF0099FFFF0066FFFF0066FFFF0066FFFF0066FFFF0066FFFF0066FFFF000099
      CC0000000000000000000000000000000000000000000000000099999900E5E5
      E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000009933
      0000CC660000CC660000CC66000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC00CCCCCC0099999900CCCCCC00CCCCCC00CCCCCC009999
      99000000000000000000000000000000000000000000000000000000000066CC
      CC0099FFFF0099FFFF0066FFFF0066FFFF000099CC0066CCCC0066CCCC0066CC
      CC00000000000000000000000000000000000000000000000000000000009999
      9900E5E5E500E5E5E500CCCCCC00CCCCCC009999990099999900999999009999
      990000000000000000000000000000000000000000000000000099330000CC66
      0000CC660000CC660000993300000000000099330000CC660000CC660000CC66
      000099330000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00999999000000000099999900CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000000000000000000000000000066CC
      CC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000099330000993300009933
      0000993300000000000000000000000000000000000000000000993300009933
      0000993300009933000000000000000000000000000099999900999999009999
      9900999999000000000000000000000000000000000000000000999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF0066FFFF000099
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF0066FF
      FF000099CC000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC00999999000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0066CCCC0066CCCC0066CCCC0066CCCC0066CCCC0066CC
      CC0066CCCC0066CCCC0000000000000000000000000000000000000000000000
      0000000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000CC9966009933000099330000CC9966000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B2009999990099999900B2B2B2000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000CC660000CC66000099330000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      000099330000CC660000CC660000993300000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      990099999900CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC660000CC660000CC660000993300000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00999999000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC6600009933000099330000CC9966000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC009999990099999900B2B2B2000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC660000CC660000CC6600009933000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999990000000000000000000000
      00000000000000000000000000000000000000000000CC99660099330000CC66
      000099330000CC99660000000000000000009933000099330000993300009933
      00009933000099330000993300000000000000000000B2B2B20099999900CCCC
      CC0099999900B2B2B20000000000000000009999990099999900999999009999
      9900999999009999990099999900000000000000000099330000CC660000CC66
      00009933000099330000CC660000CC660000CC66000099330000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC009999990099999900CCCCCC00CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      0000CC99660000000000000000000000000099330000CC660000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900B2B2B20000000000000000000000000099999900CCCCCC00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099330000CC6600009933
      0000000000000000000099330000CC660000CC660000CC660000993300000000
      0000000000000000000000000000000000000000000099999900CCCCCC009999
      9900000000000000000099999900CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000099330000CC6600009933
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000099330000993300000000
      000000000000000000000000000099330000CC660000CC660000CC6600009933
      0000000000000000000000000000000000000000000099999900999999000000
      000000000000000000000000000099999900CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000099330000CC6600009933
      0000CC99660000000000000000000000000000000000CC99660099330000CC66
      0000CC660000CC66000099330000000000000000000099999900CCCCCC009999
      9900B2B2B20000000000000000000000000000000000B2B2B20099999900CCCC
      CC00CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      00000000000000000000000000000000000099330000CC660000CC660000CC66
      0000993300000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000000099999900CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000000000000CC99660099330000CC66
      000099330000CC99660000000000CC9966009933000099330000CC6600009933
      0000CC660000CC660000993300000000000000000000B2B2B20099999900CCCC
      CC0099999900B2B2B20000000000B2B2B2009999990099999900CCCCCC009999
      9900CCCCCC00CCCCCC0099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099330000CC660000CC66
      0000CC6600009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000099999900CCCCCC00CCCC
      CC00CCCCCC00999999000000000000000000000000000000000099330000CC66
      0000CC660000993300009933000099330000CC660000CC66000099330000CC99
      660099330000CC6600009933000000000000000000000000000099999900CCCC
      CC00CCCCCC00999999009999990099999900CCCCCC00CCCCCC0099999900B2B2
      B20099999900CCCCCC0099999900000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099330000CC66
      0000CC6600009933000000000000000000000000000000000000000000000000
      000000000000000000000000000000000000000000000000000099999900CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000009933
      000099330000CC660000CC660000CC6600009933000099330000000000000000
      0000000000009933000099330000000000000000000000000000000000009999
      990099999900CCCCCC00CCCCCC00CCCCCC009999990099999900000000000000
      0000000000009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009933
      0000CC6600009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900CCCCCC009999990000000000000000000000000000000000000000000000
      0000CC996600993300009933000099330000CC99660000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000B2B2B200999999009999990099999900B2B2B20000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000993300009933000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000999999009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009933000099330000CC66000099330000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900CCCCCC0099999900CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC000099CC00000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099330000CC66000099330000CC66000099330000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900CCCCCC0099999900CCCCCC0099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066CCCC000099CC000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900999999000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009933000099330000CC66000099330000CC660000993300000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900CCCCCC0099999900CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066CCCC0099FFFF000099CC0000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900E5E5E5009999990000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099330000993300009933000099330000999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000009999990099999900999999009999990099999900999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      000066CCCC000099CC000099CC000099CC0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900999999009999990099999900CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00FFCCCC0066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      000066CCCC0099FFFF0066FFFF0066FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00FFCCCC0066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0066FFFF000099CC0066CCCC0066CCCC0066CC
      CC00000000000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500CCCCCC009999990099999900999999009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00FFCCCC0066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0066FFFF0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00FFCCCC0066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000066CCCC000099
      CC000099CC000099CC000099CC0099FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000999999009999
      9900999999009999990099999900E5E5E500CCCCCC00CCCCCC00999999000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00FFCCCC0066666600000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000099999900FFFFFF00CCCCCC0099999900000000000000
      000000000000000000000000000000000000000000000000000066CCCC0099FF
      FF0099FFFF0066FFFF0066FFFF0066FFFF0066FFFF0066FFFF0066FFFF000099
      CC0000000000000000000000000000000000000000000000000099999900E5E5
      E500E5E5E500CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC009999
      9900000000000000000000000000000000000000000000000000000000000000
      0000000000000000000066666600666666006666660066666600000000000000
      0000000000000000000000000000666666000000000000000000000000000000
      0000000000000000000099999900999999009999990099999900000000000000
      00000000000000000000000000009999990000000000000000000000000066CC
      CC0099FFFF0099FFFF0066FFFF0066FFFF000099CC0066CCCC0066CCCC0066CC
      CC00000000000000000000000000000000000000000000000000000000009999
      9900E5E5E500E5E5E500CCCCCC00CCCCCC009999990099999900999999009999
      9900000000000000000000000000000000000000000066666600666666000000
      0000000000006666660099999900999999009999990099999900666666000000
      0000000000000000000066666600666666000000000099999900999999000000
      0000000000009999990099999900999999009999990099999900999999000000
      00000000000000000000999999009999990000000000000000000000000066CC
      CC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF000099CC00000000000000
      0000000000000000000000000000000000000000000000000000000000009999
      9900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC0099999900000000000000
      0000000000000000000000000000000000009999990099999900999999006666
      66006666660099999900CCCCCC00CCCCCC00CCCCCC0099999900666666006666
      66006666660066666600CCCCCC00666666009999990099999900999999009999
      99009999990099999900CCCCCC00CCCCCC00CCCCCC0099999900999999009999
      99009999990099999900CCCCCC00999999000000000000000000000000000000
      000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF000099CC000000
      0000000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00999999000000
      00000000000000000000000000000000000099999900FFFFFF00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999
      990099999900CCCCCC00666666000000000099999900FFFFFF00CCCCCC00CCCC
      CC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00999999009999
      990099999900CCCCCC0099999900000000000000000000000000000000000000
      000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF0066FFFF000099
      CC00000000000000000000000000000000000000000000000000000000000000
      000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCCCC009999
      99000000000000000000000000000000000099999900FFFFFF00CCCCCC00CCCC
      CC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC0099999900000000000000000099999900FFFFFF00CCCCCC00CCCC
      CC00FFFFFF00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCCCC00CCCC
      CC00CCCCCC009999990000000000000000000000000000000000000000000000
      00000000000066CCCC0099FFFF0099FFFF0099FFFF0066FFFF0066FFFF0066FF
      FF000099CC000000000000000000000000000000000000000000000000000000
      00000000000099999900E5E5E500E5E5E500E5E5E500CCCCCC00CCCCCC00CCCC
      CC009999990000000000000000000000000099999900FFFFFF00FFFFFF009999
      990099999900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009999
      99009999990000000000000000000000000099999900FFFFFF00FFFFFF009999
      990099999900FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF00FFFFFF009999
      9900999999000000000000000000000000000000000000000000000000000000
      00000000000066CCCC0066CCCC0066CCCC0066CCCC0066CCCC0066CCCC0066CC
      CC0066CCCC0066CCCC0000000000000000000000000000000000000000000000
      0000000000009999990099999900999999009999990099999900999999009999
      9900999999009999990000000000000000000000000099999900999999000000
      0000000000009999990099999900999999009999990099999900999999000000
      0000000000000000000000000000000000000000000099999900999999000000
      0000000000009999990099999900999999009999990099999900999999000000
      000000000000000000000000000000000000424D3E000000000000003E000000
      2800000040000000700000000100010000000000800300000000000000000000
      000000000000000000000000FFFFFF0000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      0000000000000000000000000000000000000000000000000000000000000000
      00000000000000000000000000000000FF80FF80801F801FFF80FF80000F000F
      FE41FE41000F000FFC23FC23000F000FFC17FC17000F000FFC0FFC0F000F000F
      F807F807000F000FF803F803000F000FF003F00300000000E007E00700000000
      C03FC03F0001000180FF80FF0003000300FF00FF0007000701FF01FF000F000F
      87FF87FF800F800FCFFFCFFFC01FC01FFFFFFFFFFFFFFFFFBFFFBFFF3FFF3FFF
      9FFF9FFF0FFF0FFFCC3FCC3F83FF83FFE01FE01F80FF80FFF01FF01FC03FC03F
      E01FE01FC00FC00FE01FE01FE007E007E00FE00FE003E003E001E001F001F001
      F000F000F000F000FF00FF00F800F800FF80FF80F800F800FF80FF80FC00FC00
      FF81FF81FE00FE00FFC3FFC3FF00FF00FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      F0FFF0FFF3FFF3FFE0FFE0FFE1FFE1FFC0FFC0FFC0FFC0FF83018301807F807F
      87018701803F803F8F818F818C1F8C1F878187819E0F9E0F82018201FF07FF07
      C001C001FF83FF83E039E039FFC3FFC3F07FF07FFFE3FFE3FFFFFFFFFFF3FFF3
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFBFFFFFFFFFFF9FFF9FF
      FFFFFFFFFCFFFCFF87C387C3FC7FFC7F83838383F03FF03FC107C107F01FF01F
      E00FE00FF80FF80FF01FF01FF83FF83FF83FF83FC01FC01FF01FF01FC00FC00F
      E00FE00FE00FE00FC107C107E03FE03F83838383F01FF01F87C387C3F00FF00F
      FFFFFFFFF807F807FFFFFFFFF803F803FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF
      F3FFF3FFF0FFF0FFE1FFE1FFE0FFE0FFC0FFC0FFC0FFC0FF807F807F83018301
      803F803F870187018C1F8C1F8F818F819E0F9E0F87818781FF07FF0782018201
      FF83FF83C001C001FFC3FFC3E039E039FFE3FFE3F07FF07FFFF3FFF3FFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFBFFFBFFF81FF81FF9FFF9FFF81FF81F
      FCFFFCFFF81FF81FFC7FFC7FF81FF81FF03FF03FFC3FFC3FF01FF01FFC3FFC3F
      F80FF80FFC3FFC3FF83FF83FFC3FFC3FC01FC01FFC3FFC3FC00FC00FFC3EFC3E
      E00FE00F981C981CE03FE03F00000000F01FF01F00010001F00FF00F00030003
      F807F80700070007F803F803981F981F00000000000000000000000000000000
      000000000000}
  end
  object ColorDialog1: TColorDialog
    Left = 83
    Top = 56
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 28
    OnTimer = Timer1Timer
    Left = 24
    Top = 56
  end
end
