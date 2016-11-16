camino( E,E, C,C ).
camino( EstadoActual, EstadoFinal, CaminoHastaAhora, CaminoTotal ):-
  unPaso( EstadoActual, EstSiguiente ),
  \+member(EstSiguiente,CaminoHastaAhora),
  camino( EstSiguiente, EstadoFinal, [EstSiguiente|CaminoHastaAhora], CaminoTotal ).

solucionOptima:-
  nat(N),                        % Buscamos solucion de "coste" 0; si no, de 1, etc.
  camino([0,0],[0,4],[[0,0]],C), % En "hacer aguas": -un estado es [cubo5,cubo8], y
  length(C,N),                   % -el coste es la longitud de C.
  write(C).

unPaso([A1, A2], [S1, S2]):- S1 = 5, A1 \= S1, S2 = A2.
unPaso([A1, A2], [S1, S2]):- S2 = 8, A2 \= S2, S1 = A1.
unPaso([A1, A2], [S1, S2]):- S1 = 0, A1 \= S1, S2 = A2.
unPaso([A1, A2], [S1, S2]):- S2 = 0, A2 \= S2, S1 = A1.
unPaso([A1, A2], [S1, S2]):- T is min(A1, (8 - A2)), S1 is A1 - T, S2 is A2 + T, A1 \= S1.
unPaso([A1, A2], [S1, S2]):- T is min(A2, (5 - A1)), S2 is A2 - T, S1 is A1 + T, A2 \= S2.

nat(0).
nat(N):- nat(N1), N is N1 + 1.
