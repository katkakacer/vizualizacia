#include "RenderWindowUISingleInheritance.h"
#include "ui_RenderWindowUISingleInheritance.h"

#include <vtkGenericOpenGLRenderWindow.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkSphereSource.h>
#include <vtkCubeSource.h>
#include <vtkVersion.h>
#include <vtkPolyDataReader.h>
#include <vtkAxesActor.h>
#include <vtkTransform.h>
#include <vtkTextActor.h>

#if VTK_VERSION_NUMBER >= 89000000000ULL
#define VTK890 1
#endif

// Constructor
RenderWindowUISingleInheritance::RenderWindowUISingleInheritance(
    QWidget* parent)
  : QMainWindow(parent), ui(new Ui::RenderWindowUISingleInheritance)
{
  this->ui->setupUi(this);

  vtkNew<vtkNamedColors> colors;

  vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
#if VTK890
  this->ui->qvtkWidget->setRenderWindow(renderWindow);
#else
  this->ui->qvtkWidget->SetRenderWindow(renderWindow);
#endif

  // Sphere
  /*vtkNew<vtkSphereSource> sphereSource;
  sphereSource->Update();
  vtkNew<vtkPolyDataMapper> sphereMapper;
  sphereMapper->SetInputConnection(sphereSource->GetOutputPort());
  vtkNew<vtkActor> sphereActor;
  sphereActor->SetMapper(sphereMapper);
  sphereActor->GetProperty()->SetColor(colors->GetColor4d("Tomato").GetData());*/

  //Cube
   /* vtkNew<vtkCubeSource> cubeSource;
    cubeSource->Update();
    vtkNew<vtkPolyDataMapper> cubeMapper;
    cubeMapper->SetInputConnection(cubeSource->GetOutputPort());
    vtkNew<vtkActor> cubeActor;
    cubeActor->SetMapper(cubeMapper);
    cubeActor->GetProperty()->SetColor(colors->GetColor4d("Blue").GetData());*/

  vtkSmartPointer<vtkPolyData> polyData;
  vtkNew<vtkPolyDataReader> reader;
  reader->SetFileName("D:/Downloads/RenderWindowUISingleInheritance/RenderWindowUISingleInheritance/sfera.vtk");
  reader->Update();
  polyData = reader->GetOutput();
  vtkNew<vtkPolyDataMapper> mapper;
  mapper->SetInputData(polyData);
  vtkNew<vtkActor> actor;
  actor->SetMapper(mapper);
  actor->GetProperty()->SetColor(colors->GetColor4d("Blue").GetData());
  vtkNew<vtkTransform> transform;
  transform->Translate(actor->GetCenter()[0]-1, actor->GetCenter()[1]-1,
      actor->GetCenter()[2]-1);
  vtkNew<vtkAxesActor> axes;
  double l[3];
  l[0] = (actor->GetBounds()[1] - actor->GetBounds()[0]) * 0.5;
  l[1] = (actor->GetBounds()[3] - actor->GetBounds()[2]) * 0.5;
  l[2] = (actor->GetBounds()[5] - actor->GetBounds()[4]) * 0.5;

  axes->SetTotalLength(l);
  axes->SetUserTransform(transform);

  vtkNew<vtkTextActor> text;
  text->SetDisplayPosition(10, 10);
  text->SetInput("sfera");
  text->SetHeight(50);

  // VTK Renderer
  vtkNew<vtkRenderer> renderer;
  renderer->AddActor(actor);
  renderer->AddActor(axes);
  renderer->AddActor(text);
  //renderer->AddActor(sphereActor);
  renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
  //renderer->AddActor(cubeActor);
  //renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

  // VTK/Qt wedded
#if VTK890
  this->ui->qvtkWidget->renderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->renderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#else
  this->ui->qvtkWidget->GetRenderWindow()->AddRenderer(renderer);
  this->ui->qvtkWidget->GetRenderWindow()->SetWindowName(
      "RenderWindowUISingleInheritance");
#endif
  // Set up action signals and slots
  connect(this->ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

RenderWindowUISingleInheritance::~RenderWindowUISingleInheritance()
{
  delete this->ui;
}

void RenderWindowUISingleInheritance::slotExit()
{
  qApp->exit();
}
