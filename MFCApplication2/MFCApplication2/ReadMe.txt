================================================================================
    MICROSOFT FOUNDATION CLASS LIBRARY : MFCApplication2 Project Overview
===============================================================================

The application wizard has created this MFCApplication2 application for
you.  This application not only demonstrates the basics of using the Microsoft
Foundation Classes but is also a starting point for writing your application.

This file contains a summary of what you will find in each of the files that
make up your MFCApplication2 application.

MFCApplication2.vcxproj
    This is the main project file for VC++ projects generated using an application wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    application wizard.

MFCApplication2.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

MFCApplication2.h
    This is the main header file for the application.  It includes other
    project specific headers (including Resource.h) and declares the
    CMFCApplication2App application class.

MFCApplication2.cpp
    This is the main application source file that contains the application
    class CMFCApplication2App.

MFCApplication2.rc
    This is a listing of all of the Microsoft Windows resources that the
    program uses.  It includes the icons, bitmaps, and cursors that are stored
    in the RES subdirectory.  This file can be directly edited in Microsoft
    Visual C++. Your project resources are in 1033.

res\MFCApplication2.ico
    This is an icon file, which is used as the application's icon.  This
    icon is included by the main resource file MFCApplication2.rc.

res\MFCApplication2.rc2
    This file contains resources that are not edited by Microsoft
    Visual C++. You should place all resources not editable by
    the resource editor in this file.

MFCApplication2.reg
    This is an example .reg file that shows you the kind of registration
    settings the framework will set for you.  You can use this as a .reg
    file to go along with your application or just delete it and rely
    on the default RegisterShellFileTypes registration.


/////////////////////////////////////////////////////////////////////////////

For the main frame window:
    The project includes a standard MFC interface.

MainFrm.h, MainFrm.cpp
    These files contain the frame class CMainFrame, which is derived from
    CMDIFrameWnd and controls all MDI frame features.

res\Toolbar.bmp
    This bitmap file is used to create tiled images for the toolbar.
    The initial toolbar and status bar are constructed in the CMainFrame
    class. Edit this toolbar bitmap using the resource editor, and
    update the IDR_MAINFRAME TOOLBAR array in MFCApplication2.rc to add
    toolbar buttons.
/////////////////////////////////////////////////////////////////////////////

For the child frame window:

ChildFrm.h, ChildFrm.cpp
    These files define and implement the CChildFrame class, which
    supports the child windows in an MDI application.

/////////////////////////////////////////////////////////////////////////////

The application wizard creates one document type and one view:

MFCApplication2Doc.h, MFCApplication2Doc.cpp - the document
    These files contain your CMFCApplication2Doc class.  Edit these files to
    add your special document data and to implement file saving and loading
    (via CMFCApplication2Doc::Serialize).
    The Document will have the following strings:
        File extension:      fig
        File type ID:        MFCApplication2.Document
        Main frame caption:  MFCApplication2
        Doc type name:       MFCApplication2
        Filter name:         MFCApplication2 Files (*.fig)
        File new short name: MFCApplication2
        File type long name: MFCApplication2.Document

MFCApplication2View.h, MFCApplication2View.cpp - the view of the document
    These files contain your CMFCApplication2View class.
    CMFCApplication2View objects are used to view CMFCApplication2Doc objects.

res\MFCApplication2Doc.ico
    This is an icon file, which is used as the icon for MDI child windows
    for the CMFCApplication2Doc class.  This icon is included by the main
    resource file MFCApplication2.rc.



/////////////////////////////////////////////////////////////////////////////

Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named MFCApplication2.pch and a precompiled types file named StdAfx.obj.

Resource.h
    This is the standard header file, which defines new resource IDs.
    Microsoft Visual C++ reads and updates this file.

/////////////////////////////////////////////////////////////////////////////

Other notes:

The application wizard uses "TODO:" to indicate parts of the source code you
should add to or customize.

If your application uses MFC in a shared DLL, you will need
to redistribute the MFC DLLs. If your application is in a language
other than the operating system's locale, you will also have to
redistribute the corresponding localized resources mfc110XXX.DLL.
For more information on both of these topics, please see the section on
redistributing Visual C++ applications in MSDN documentation.

/////////////////////////////////////////////////////////////////////////////
