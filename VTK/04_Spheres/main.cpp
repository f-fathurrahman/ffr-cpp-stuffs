// typical setup is:
//
// source -> mapper -> actor -> renderer -> renderwindow
//

#include <cstdio>

#include <vtkSphereSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main( int argc, char **argv )
{

    vtkSphereSource *sphere = vtkSphereSource::New();
    sphere->SetRadius( 1.0 );
    sphere->SetThetaResolution( 10 );
    sphere->SetPhiResolution( 10 );

    vtkSphereSource *sphere2 = vtkSphereSource::New();
    sphere2->SetRadius( 2.0 );
    sphere2->SetThetaResolution( 100 );
    sphere2->SetPhiResolution( 100 );
    double center[3] = {3.0, 3.0, 3.0};
    sphere2->SetCenter( center );

    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    vtkActor *actor = vtkActor::New();

    vtkPolyDataMapper *mapper2 = vtkPolyDataMapper::New();
    vtkActor *actor2 = vtkActor::New();
    
    vtkRenderer *renderer = vtkRenderer::New();

    mapper->SetInputConnection( sphere->GetOutputPort() );
    actor->SetMapper( mapper );

    mapper2->SetInputConnection( sphere2->GetOutputPort() );
    actor2->SetMapper( mapper2 );


    renderer->AddActor( actor );
    renderer->AddActor( actor2 );
    renderer->SetBackground( 0.0, 0.0, 0.5 );

    // create the render window
    vtkRenderWindow *window = vtkRenderWindow::New();
    window->AddRenderer( renderer );
    window->SetSize( 300, 300 );

    vtkRenderWindowInteractor *windowInteractor = vtkRenderWindowInteractor::New();
    windowInteractor->SetRenderWindow( window );

    windowInteractor->Start();

    // Free memory
    sphere->Delete();
    mapper->Delete();
    actor->Delete();
    renderer->Delete();
    window->Delete();
    windowInteractor->Delete();

    return 0;
}