// typical setup is:
//
// source -> mapper -> actor -> renderer -> renderwindow
//

#include <cstdio>

#include <vtkCylinderSource.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkCamera.h>

int main( int argc, char **argv )
{

    vtkCylinderSource *cylinder = vtkCylinderSource::New();
    printf("default height = %f\n", cylinder->GetHeight());
    cylinder->SetHeight( 5.0 );
    cylinder->SetRadius( 1.0 );
    cylinder->SetResolution( 30 );

    // vtkPolyDataMapper is used to map the polygonal data into graphics primitive.
    vtkPolyDataMapper *mapper = vtkPolyDataMapper::New();
    mapper->SetInputConnection( cylinder->GetOutputPort() );

    // create an actor to represent the source.
    vtkActor *actor = vtkActor::New();
    actor->SetMapper( mapper );

    // create the renderer and assign actor(s) to it.
    vtkRenderer *renderer = vtkRenderer::New();
    renderer->AddActor( actor );
    renderer->SetBackground( 0.0, 0.0, 0.5 );

    // create the render window
    vtkRenderWindow *window = vtkRenderWindow::New();
    window->AddRenderer( renderer );
    window->SetSize( 300, 300 );

    vtkRenderWindowInteractor *windowInteractor = vtkRenderWindowInteractor::New();
    windowInteractor->SetRenderWindow( window );

    windowInteractor->Start();

    // Free memory
    cylinder->Delete();
    mapper->Delete();
    actor->Delete();
    renderer->Delete();
    window->Delete();
    windowInteractor->Delete();

    return 0;
}