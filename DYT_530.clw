; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDYT_530View
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "DYT_530.h"
LastPage=0

ClassCount=6
Class1=CDYT_530App
Class2=CDYT_530Doc
Class3=CDYT_530View
Class4=CMainFrame

ResourceCount=3
Resource1=IDR_MAINFRAME
Class5=CAboutDlg
Resource2=IDD_ABOUTBOX
Class6=CDialogHistergram
Resource3=IDD_DIALOG1

[CLS:CDYT_530App]
Type=0
HeaderFile=DYT_530.h
ImplementationFile=DYT_530.cpp
Filter=N

[CLS:CDYT_530Doc]
Type=0
HeaderFile=DYT_530Doc.h
ImplementationFile=DYT_530Doc.cpp
Filter=N
BaseClass=CDocument
VirtualFilter=DC
LastObject=CDYT_530Doc

[CLS:CDYT_530View]
Type=0
HeaderFile=DYT_530View.h
ImplementationFile=DYT_530View.cpp
Filter=C
LastObject=ID_D
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame
BaseClass=CFrameWnd
VirtualFilter=fWC




[CLS:CAboutDlg]
Type=0
HeaderFile=DYT_530.cpp
ImplementationFile=DYT_530.cpp
Filter=D
LastObject=GRAY

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_PRINT
Command6=ID_FILE_PRINT_PREVIEW
Command7=ID_FILE_PRINT_SETUP
Command8=ID_FILE_MRU_FILE1
Command9=ID_APP_EXIT
Command10=ID_EDIT_UNDO
Command11=ID_EDIT_CUT
Command12=ID_EDIT_COPY
Command13=ID_EDIT_PASTE
Command14=ID_VIEW_TOOLBAR
Command15=ID_VIEW_STATUS_BAR
Command16=ID_APP_ABOUT
CommandCount=16

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
Command9=GRAY
Command10=ID_EQUALIZE
Command11=ID_Histogram
Command12=ID_LINEAR
Command13=ID_AverageFilter
Command14=ID_MediumFilter
Command15=ID_GradSharp
Command16=ID_RaplasSharp
Command17=ID_Fourier
Command18=ID_Ifourier
Command19=ID_Fft
Command20=ID_Ifft
Command21=ID_D
CommandCount=21

[DLG:IDD_DIALOG1]
Type=1
Class=CDialogHistergram
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816

[CLS:CDialogHistergram]
Type=0
HeaderFile=DialogHistergram.h
ImplementationFile=DialogHistergram.cpp
BaseClass=CDialog
Filter=D
LastObject=CDialogHistergram
VirtualFilter=dWC

