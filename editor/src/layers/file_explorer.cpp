/*
 * Copyright © 2026. Proton Engine
 * Licensed using the MIT license
 */

#include "file_explorer.h"

#include "protonengine/ui/widgets.h"

namespace ProtonEditor::Layers
{

FileExplorer::FileExplorer() : Layer("File Explorer")
{
}

void FileExplorer::onAttach()
{
}

void FileExplorer::onImGuiRender()
{
    ProtonEngine::Ui::Widgets::Text("No project loaded");
}

void FileExplorer::onUpdate(float timeStep)
{
}

} // namespace ProtonEditor::Layers