from pathlib import Path
import subprocess
import sys


def main():
    base_dir = Path(__file__).resolve().parent
    program = base_dir / "gnomos.py"
    tests_dir = base_dir
    input_files = sorted(tests_dir.glob("*.in"))

    if not input_files:
        print("Nenhum arquivo .in foi encontrado.")
        return

    for input_file in input_files:
        expected_file = input_file.with_suffix(".out")

        print(f"Teste: {input_file.name}")

        input_data = input_file.read_text(encoding="utf-8")
        result = subprocess.run(
            [sys.executable, str(program)],
            input=input_data,
            capture_output=True,
            text=True,
            encoding="utf-8",
            check=False,
        )

        output = result.stdout.strip()
        print("Saida do programa:")
        print(output if output else "(sem saida)")

        if result.stderr.strip():
            print("Erros:")
            print(result.stderr.strip())

        if expected_file.exists():
            expected_output = expected_file.read_text(encoding="utf-8").strip()
            print("Saida esperada:")
            print(expected_output if expected_output else "(sem saida)")
            print("Resultado:", "OK" if output == expected_output else "DIVERGENTE")
        else:
            print("Saida esperada: arquivo .out nao encontrado")

        print("-" * 40)


if __name__ == "__main__":
    main()
