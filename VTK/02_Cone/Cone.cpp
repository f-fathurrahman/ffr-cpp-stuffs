// typical setup is:
//
// source -> mapper -> actor -> renderer -> renderwindow
//

#include <vtkConeSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main( int argc, char **argv )
{
    // create an instance of vtkConeSource and set some of its properties.
    vtkConeSource *cone = vtkConeSource::New();
    cone->SetHeight( 3.0 );
    cone->SetRadius( 1.0 );
    cone->SetResolution( 30 );

    // vtkPolyDataMapper is used to map the polygonal data into graphics primitive.
    vtkPolyDataMapper *coneMapper = vtkPolyDataMapper::New();
    // coneMapper->SetInput( cone->GetOutput() );
    coneMapper->SetInputConnection( cone->GetOutputPort() );

    // create an actor to represent the cone.
    vtkActor *coneActor = vtkActor::New();
    coneActor->SetMapper( coneMapper );

    // create the renderer and assign actor(s) to it.
    vtkRenderer *renderer = vtkRenderer::New();
    renderer->AddActor( coneActor );
    renderer->SetBackground( 0.1, 0.2, 0.4 );

    // create the render window
    vtkRenderWindow *window = vtkRenderWindow::New();
    window->AddRenderer( renderer );
    window->SetSize( 300, 300 );

    vtkRenderWindowInteractor *windowInteractor = vtkRenderWindowInteractor::New();
    windowInteractor->SetRenderWindow( window );

    windowInteractor->Start();

    // Free memory
    cone->Delete();
    coneMapper->Delete();
    coneActor->Delete();
    renderer->Delete();
    window->Delete();
    windowInteractor->Delete();

    return 0;
}