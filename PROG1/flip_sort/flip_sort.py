import sys

def merge_and_count(arr, temp, left, mid, right):
    # i percorre a metade esquerda, j a metade direita e k escreve no vetor auxiliar.
    i = left
    j = mid + 1
    k = left
    # Acumula as inversões encontradas entre as duas metades.
    inversions = 0

    while i <= mid and j <= right:
        # Se o elemento da esquerda já é menor ou igual, ele mantém a ordem.
        if arr[i] <= arr[j]:
            temp[k] = arr[i]
            i += 1
        else:
            # arr[j] é menor que arr[i], então ele forma inversão com todos
            # os elementos restantes da metade esquerda.
            temp[k] = arr[j]
            inversions += mid - i + 1
            j += 1
        k += 1

    # Copia para o auxiliar os elementos que sobraram da metade esquerda.
    while i <= mid:
        temp[k] = arr[i]
        i += 1
        k += 1

    # Copia para o auxiliar os elementos que sobraram da metade direita.
    while j <= right:
        temp[k] = arr[j]
        j += 1
        k += 1

    # Atualiza o trecho original com os elementos agora ordenados.
    for idx in range(left, right + 1):
        arr[idx] = temp[idx]

    return inversions


def merge_sort_and_count(arr, temp, left, right):
    # Um trecho com 0 ou 1 elemento já está ordenado.
    if left >= right:
        return 0

    # Divide o intervalo atual em duas metades.
    mid = (left + right) // 2

    # Soma as inversões da esquerda, da direita e do merge.
    inversions = merge_sort_and_count(arr, temp, left, mid)
    inversions += merge_sort_and_count(arr, temp, mid + 1, right)
    inversions += merge_and_count(arr, temp, left, mid, right)

    return inversions


def count_minimum_exchanges(values):
    # Vetor vazio não precisa de nenhuma troca.
    if not values:
        return 0

    # Faz uma cópia para preservar a lista original.
    arr = values[:]
    # Vetor auxiliar usado pelo Merge Sort durante as intercalações dos vetores.
    temp = [0] * len(arr)
    return merge_sort_and_count(arr, temp, 0, len(arr) - 1)


def main():
    # Lê toda a entrada e a separa.
    data = sys.stdin.read().split()
    if not data:
        return

    index = 0
    # Armazena as linhas de saída para imprimir tudo de uma vez ao final.
    output = []

    while index < len(data):
        # Cada caso começa com a quantidade de elementos.
        n = int(data[index])
        index += 1

        # N igual a zero indica o fim da entrada.
        if n == 0:
            break

        # Lê os N valores do caso atual.
        values = list(map(int, data[index:index + n]))
        index += n

        # O número mínimo de trocas adjacentes é igual ao número de inversões.
        exchanges = count_minimum_exchanges(values)
        output.append(f"Minimum exchange operations : {exchanges}")

    # Imprime uma resposta por linha, no formato pedido pelo enunciado.
    sys.stdout.write("\n".join(output))


if __name__ == "__main__":
    # Executa o programa apenas quando este arquivo é chamado diretamente.
    main()
