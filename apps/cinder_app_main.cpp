#include <visualizer/natural_selection_app.h>

void prepareSettings(naturalselection::NaturalSelectionApp::Settings* settings) {
    settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(naturalselection::NaturalSelectionApp, ci::app::RendererGl, prepareSettings);