cmake_minimum_required(VERSION 3.10)
project(ing1_quoridor_2024_groupe12_8 C)

set(CMAKE_C_STANDARD 99)

# Utilisation d'un chemin valide (évitez les espaces dans les répertoires si possible)
include_directories("MAIN - main/sousp1/header")

# Définition de la cible avec tous les fichiers source
add_executable(ing1_quoridor_2024_groupe12_8
        "MAIN - main/header.h"
        "MAIN - main/main.c"
        "MAIN - main/sousp1.c"
        "MAIN - main/Tableau.c"
)

# Lien avec les bibliothèques Windows (si sur Windows)
if(WIN32)
    target_link_libraries(ing1_quoridor_2024_groupe12_8
            kernel32 user32 gdi32 winspool shell32 ole32 oleaut32 uuid comdlg32 advapi32
    )
endif()