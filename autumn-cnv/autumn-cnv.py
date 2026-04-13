import os
import sys
import subprocess
import tarfile
import shutil

def luato_atm(source_file, output_binary):
	try:
		subprocess.run(['luac', '-o', output_binary, source_file], check=True)
		return True
	except Exception as e:
		print(f"Compiler error! ({source_file}): {e}")
		return False

def pack_atmapp(source_dir):
	app_name = os.path.basename(source_dir.strip("/"))
	temp_build_dir = f"/tmp/{app_name}_build"
	output_pkg = f"{app_name}.atm"

	if os.path.exists(temp_build_dir):
		shutil.rmtree(temp_build_dir)
	os.makedirs(temp_build_dir)

	print(f"Converting '{app_name}' to Autumn compatible binary...")
	for root, dirs, files in os.walk(source_dir):
        for file in files:
            src_path = os.path.join(root, file)
            rel_path = os.path.relpath(src_path, source_dir)
            dest_path = os.path.join(temp_build_dir, rel_path)

            os.makedirs(os.path.dirname(dest_path), exist_ok=True)

            if file.endswith(".lua"):
                if compile_lua_to_binary(src_path, dest_path):
                    print(f"  [Compiled] {rel_path}")
            else:
                shutil.copy2(src_path, dest_path)
                print(f"  [Asset]    {rel_path}")

    with tarfile.open(output_pkg, "w:gz") as tar:
        tar.add(temp_build_dir, arcname=app_name)

    shutil.rmtree(temp_build_dir)
    print(f"Successfully compiled {output_pkg}!")

if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Using: atm-conv <app_folder>")
    else:
        pack_atmapp(sys.argv[1])
