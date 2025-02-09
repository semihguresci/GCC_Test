import subprocess
import sys
import platform

def run_command(command):
    try:
        result = subprocess.run(command, check=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        print(result.stdout)
    except subprocess.CalledProcessError as e:
        print(f"Error: {e.stderr}")
        sys.exit(1)

def build_docker_image(image_name="gcctest"):
    print(f"Building Docker image '{image_name}'...")
    run_command(["docker", "build", "-t", image_name, "."])
    print("Docker image built successfully!")

def run_docker_container(image_name="gcctest"):
    print(f"Running Docker container from image '{image_name}'...")
    run_command(["docker", "run", "--rm", image_name])
    print("Docker container ran successfully!")

if __name__ == "__main__":
    print(f"Platform: {platform.system()} {platform.release()}")
    
    build_docker_image()
    run_docker_container()
