#include <iostream>
#include <wx-3.2/wx/wx.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <wx-3.2/wx/glcanvas.h>
#include <cstdlib>
#include <ctime>

class MyApp : public wxApp
{
public:
    virtual bool OnInit();
};

class MyGLCanvas; // Forward declaration of MyGLCanvas

class MyFrame : public wxFrame
{
public:
    MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size);

private:
    void OnNewTriangle(wxCommandEvent &event);
    void OnChangeColor(wxCommandEvent &event);
    MyGLCanvas *m_glCanvas;
};

class MyGLCanvas : public wxGLCanvas
{
public:
    MyGLCanvas(wxFrame *parent);
    void OnPaint(wxPaintEvent &event);
    void OnShow(wxShowEvent &event);
    void NewTriangle();
    void ChangeColor();

private:
    wxGLContext *m_context;
    bool m_glewInitialized;
    float m_triangleColor[3];
};

IMPLEMENT_APP(MyApp)

bool MyApp::OnInit()
{
    std::srand(static_cast<unsigned int>(std::time(0)));
    MyFrame *frame = new MyFrame("wxWidgets OpenGL Boilerplate", wxPoint(50, 50), wxSize(800, 600));
    frame->Show(true);
    return true;
}

MyFrame::MyFrame(const wxString &title, const wxPoint &pos, const wxSize &size)
    : wxFrame(NULL, wxID_ANY, title, pos, size)
{
    // Create menu bar and menu items
    wxMenu *menuFile = new wxMenu;
    menuFile->Append(wxID_NEW, "&New Triangle\tCtrl-N", "Create a new triangle");

    wxMenuBar *menuBar = new wxMenuBar;
    menuBar->Append(menuFile, "&File");
    SetMenuBar(menuBar);

    // Create change color button
    wxButton *changeColorButton = new wxButton(this, wxID_ANY, wxT("Change Color"), wxDefaultPosition, wxDefaultSize, 0);
    changeColorButton->Bind(wxEVT_BUTTON, &MyFrame::OnChangeColor, this);

    // Create OpenGL canvas
    m_glCanvas = new MyGLCanvas(this);

    // Set up sizer for button and canvas
    wxBoxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    sizer->Add(changeColorButton, 0, wxEXPAND);
    sizer->Add(m_glCanvas, 1, wxEXPAND);

    SetSizer(sizer);

    // Bind menu events
    Bind(wxEVT_MENU, &MyFrame::OnNewTriangle, this, wxID_NEW);
}

void MyFrame::OnNewTriangle(wxCommandEvent &event)
{
    m_glCanvas->NewTriangle();
}

void MyFrame::OnChangeColor(wxCommandEvent &event)
{
    m_glCanvas->ChangeColor();
}

MyGLCanvas::MyGLCanvas(wxFrame *parent)
    : wxGLCanvas(parent, wxID_ANY, nullptr, wxDefaultPosition, wxDefaultSize, wxFULL_REPAINT_ON_RESIZE),
      m_context(new wxGLContext(this)), m_glewInitialized(false)
{
    Connect(wxEVT_PAINT, wxPaintEventHandler(MyGLCanvas::OnPaint));
    Connect(wxEVT_SHOW, wxShowEventHandler(MyGLCanvas::OnShow));
    NewTriangle();
    ChangeColor();
}

void MyGLCanvas::OnShow(wxShowEvent &event)
{
    if (!m_glewInitialized)
    {
        SetCurrent(*m_context);
        if (glewInit() != GLEW_OK)
        {
            std::cerr << "Failed to initialize GLEW\n";
            exit(EXIT_FAILURE);
        }
        m_glewInitialized = true;
    }
    event.Skip();
}

void MyGLCanvas::OnPaint(wxPaintEvent &event)
{
    wxPaintDC(this);
    SetCurrent(*m_context);
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_TRIANGLES);
    glColor3f(m_triangleColor[0], m_triangleColor[1], m_triangleColor[2]);
    glVertex3f(-0.5f, -0.5f, 0.0f);
    glVertex3f(0.5f, -0.5f, 0.0f);
    glVertex3f(0.0f, 0.5f, 0.0f);
    glEnd();

    glFlush();
    SwapBuffers();
}

void MyGLCanvas::NewTriangle()
{
    // Add logic for generating a new triangle if needed.
}

void MyGLCanvas::ChangeColor()
{
    m_triangleColor[0] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
    m_triangleColor[1] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
    m_triangleColor[2] = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX));
    Refresh();
}