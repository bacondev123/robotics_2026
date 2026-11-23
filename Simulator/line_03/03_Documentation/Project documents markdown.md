# Sword Art Online — Project Guidelines & Sync Rules

This document outlines the workflow constraints, naming standards, and syncing procedures for developers working on the Sword Art Online project.

---

## 🛠️ Rojo File Sync Mapping

To sync local scripts from VS Code into Roblox Studio, you must use the proper extensions. Rojo identifies the instance class based on these suffixes:

| VS Code File Extension | Target Roblox Class | Description |
| :--- | :--- | :--- |
| `.server.luau` | `Script` | Code running on the server. |
| `.client.luau` | `LocalScript` | Code running on the client. |
| `.luau` | `ModuleScript` | Reusable library or service module. |

---

## 📂 Project Tree Reference

```text
Sword_Art_Online/
├── 01_Production/          # Active source code and tool workspaces
│   └── SAO_Workspace/      # Rojo project directory
│       ├── src/
│       │   ├── client/     # Client code (mapped to StarterPlayerScripts)
│       │   ├── server/     # Server code (mapped to ServerScriptService)
│       │   └── shared/     # Shared modules (mapped to ReplicatedStorage)
│       └── default.project.json
├── 02_Assets/              # Game assets (never synced via Rojo)
│   ├── 3D_Models/          # Raw and exported FBX assets
│   ├── UI_Graphics/        # Figma designs, icons, and UI exports
│   └── Audio/              # Sound effects and soundtrack files
├── 03_Documentation/       # Game design and workflow documentation
│   └── HINTS.md            # This document
└── 04_Archive/             # Deprecated code and older place files
    ├── Deprecated/         # Discarded script drafts
    └── Legacy/             # Historical .rbxl studio files