def write_kd():
    filename = input("Enter file name (without extension): ")
    text = input("Enter text: ")

    hex_data = text.encode().hex()

    with open(filename + ".kd", "w") as f:
        f.write(hex_data)

    print("Data saved to", filename + ".kd")


def read_kd():
    filename = input("Enter file name (without extension): ")

    try:
        with open(filename + ".kd", "r") as f:
            hex_data = f.read()

        text = bytes.fromhex(hex_data).decode()

        print("\nDecoded Text:")
        print(text)

    except FileNotFoundError:
        print("File not found!")
    except Exception as e:
        print("Error:", e)


while True:
    print("\n1. Write KD File")
    print("2. Read KD File")
    print("3. Exit")

    choice = input("Choice: ")

    if choice == "1":
        write_kd()
    elif choice == "2":
        read_kd()
    elif choice == "3":
        break
    else:
        print("Invalid choice")

