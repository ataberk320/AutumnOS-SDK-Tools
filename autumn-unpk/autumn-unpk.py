import os
import tarfile
import shutil

def unpackage(atm_file, target_root="/apps"):
    try:
        if not atm_file.endswith(".atm"):
            print("Error, this file is not an Autumn archive!");
            return False

        print(f"Unpacking {atm_file}")
        with tarfile.open(atm_file, "r:gz") as tar:
            app_name = tar.getnames()[0].split("/")[0]
            install_path = os.path.join(target_root, app_name)
            if os.path.exists(install_path):
                shutil.rmtree(install_path)
            tar.extractall(path=target_root)
          print(f"{app_name} successfully unpackaged and loaded to {install_path}!);
          return True
      except Exception as e:
        print (f"Error while unpackaging process: {e}!")
        return False
