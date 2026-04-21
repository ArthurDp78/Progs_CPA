import sys

def find_award_index(thresholds, score, left, right):
    # Busca binaria recursiva para localizar a primeira faixa cujo limite e maior que a pontuacao.
    # Quando left ultrapassa right, left indica exatamente a faixa correta.
    if left > right:
        return left

    # Divide o intervalo atual de busca ao meio.
    mid = (left + right) // 2

    # Se a pontuacao for menor que o limite central, a resposta esta na metade esquerda.
    if score < thresholds[mid]:
        return find_award_index(thresholds, score, left, mid - 1)

    # Caso contrario, a faixa correta esta da posicao mid para a direita.
    return find_award_index(thresholds, score, mid + 1, right)


def main():
    # Le toda a entrada e separa os valores por espacos e quebras de linha.
    data = sys.stdin.read().split()
    if not data:
        return

    index = 0
    # N = numero de faixas de premiacao, M = numero de alunos.
    n = int(data[index])
    index += 1
    m = int(data[index])
    index += 1

    # Limites que separam uma faixa da outra.
    thresholds = list(map(int, data[index:index + n - 1]))
    index += n - 1

    # Premio associado a cada uma das N faixas.
    awards = list(map(int, data[index:index + n]))
    index += n

    # Pontuacoes obtidas pelos M alunos.
    scores = list(map(int, data[index:index + m]))

    result = []
    for score in scores:
        # Descobre em qual faixa a pontuacao do aluno se encaixa.
        award_index = find_award_index(thresholds, score, 0, len(thresholds) - 1)
        # Usa o indice da faixa para recuperar o premio correspondente.
        result.append(str(awards[award_index]))

    # Imprime os premios na mesma ordem em que os alunos foram informados.
    sys.stdout.write(" ".join(result))

if __name__ == "__main__":
    # Executa o programa somente quando este arquivo e chamado diretamente.
    main()
