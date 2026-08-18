def organizar_cartas(cartas, n):
    for i, dano_i in enumerate(cartas):
        for j, dano_j in enumerate(cartas[i+1:n-1]):
            if dano_j == dano_i:
                cartas[j], cartas[j+1] = cartas[j+1], cartas[j]


def calcular_dano(cartas):
    pass

def main():
    casos = int(input())
    for caso in range(casos):
        n = int(input())
        cartas = list(map(int, input().split()))

        organizar_cartas(cartas, n)
        print(calcular_dano(cartas))

