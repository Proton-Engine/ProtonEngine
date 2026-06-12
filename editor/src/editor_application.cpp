/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "editor_application.h"

#include "layers/editor_view.h"
#include "layers/file_explorer.h"
#include "layers/menu_bar.h"
#include "layers/properties.h"
#include "layers/scene_hierarchy.h"
#include "protonengine/ui/debug_layer.h"

ProtonEditor::SandboxApplication::SandboxApplication() : Application("Proton Editor")
{
}

void ProtonEditor::SandboxApplication::initialize()
{
    addLayer(std::make_unique<Layers::SceneHierarchyLayer>());
    addLayer(std::make_unique<Layers::FileExplorer>());
    addLayer(std::make_unique<Layers::EditorView>());
    addLayer(std::make_unique<Layers::Properties>());
    addLayer(std::make_unique<Layers::MenuBar>());
}