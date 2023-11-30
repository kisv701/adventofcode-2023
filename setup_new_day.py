from argparse import ArgumentParser
from pathlib import Path
from textwrap import dedent

def parse_args():
    parser = ArgumentParser(
        description="Creates a folder for the day and adds cmake boilerplate into the created folder."
        )
    parser.add_argument("day", type=int, help="Day in december, e.g. 24 for christmas eve.")
    return parser.parse_args()

def create_cmakelists(dirpath: Path, day: int):
    cmake_boilerplate = dedent(f"""
    set(APPLICATION_NAME day_{day})

    file(GLOB SOURCES ${{CMAKE_SOURCE_DIR}} "*.cpp" "*.h")

    add_executable(
      ${{APPLICATION_NAME}}
      ${{SOURCES}}
    )

    include_directories("${{CMAKE_SOURCE_DIR}}/utils")
    target_link_libraries(${{APPLICATION_NAME}} PUBLIC utils)

    configure_file(input.txt input.txt COPYONLY)
    """).lstrip("\n")

    filename = dirpath / "CMakeLists.txt"
    if filename.exists():
        raise FileExistsError(f"CMakeLists.txt in {dirpath} already exists.")
    
    with open(filename, "w") as f:
        f.write(cmake_boilerplate)


def create_main(dirpath: Path):
    cpp_boilerplate = dedent("""
    #include <iostream>

    int main()
    {
        std::cout << "Hello World\\n";
        return 0;
    }
    """).lstrip("\n")

    filename = dirpath / "main.cpp"
    if filename.exists():
        raise FileExistsError(f"main.cpp in {dirpath} already exists.")
    
    with open(filename, "w") as f:
        f.write(cpp_boilerplate)

def create_input(dirpath: Path):
    filename = dirpath / "input.txt"
    if filename.exists():
        raise FileExistsError(f"input.txt in {dirpath} already exists.")
    
    with open(filename, "w") as f:
        f.write("")

def create_dir(day: int) -> Path:
    dirpath = Path(f"day_{day}")
    if dirpath.exists():
        raise FileExistsError(f"Folder {dirpath} already exists.")
    
    dirpath.mkdir()
    return dirpath

def main():
    args = parse_args()

    day_dir = create_dir(args.day)
    create_cmakelists(day_dir, args.day)
    create_main(day_dir)
    create_input(day_dir)

if __name__ == '__main__':
    main()