# compare_files.py

def compare_txt_files(file1_path, file2_path):
    # Read both files into lists of lines
    with open(file1_path, 'r', encoding='utf-8') as f1:
        file1_lines = f1.readlines()
    with open(file2_path, 'r', encoding='utf-8') as f2:
        file2_lines = f2.readlines()

    max_lines = max(len(file1_lines), len(file2_lines))
    differences_found = False

    for i in range(max_lines):
        line1 = file1_lines[i].rstrip("\n") if i < len(file1_lines) else "<No line>"
        line2 = file2_lines[i].rstrip("\n") if i < len(file2_lines) else "<No line>"

        if line1 != line2:
            differences_found = True
            print(f"Difference at line {i+1}:")
            print(f"File 1: {line1}")
            print(f"File 2: {line2}")
            print("-" * 40)

    if not differences_found:
        print("✅ Both files are identical.")

if __name__ == "__main__":
    file1 = "file1.txt"
    file2 = "file2.txt"
    compare_txt_files(file1, file2)
