camino( E,E, C,C, _ ).
camino( EstadoActual, EstadoFinal, CaminoHastaAhora, CaminoTotal, N ):-
  unPaso( EstadoActual, EstSiguiente, N),
  \+member(EstSiguiente,CaminoHastaAhora),
  camino( EstSiguiente, EstadoFinal, [EstSiguiente|CaminoHastaAhora], CaminoTotal, N).

%Contem la posició inicila com a primer pas
solucionOptima(P, N):-
  N > 0,                        % Buscamos solucion de "coste" 0; si no, de 1, etc.
  camino([0,0],[0,4,[[0,0]],C, N), % En "hacer aguas": -un estado es [cubo5,cubo8], y
  (length(C,P); !, fail),                   % -el coste es la longitud de C.
  write(C).

unPaso([A1, A2], [S1, S2], N):- S1 is A1+2, S2 is A2+1, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1+2, S2 is A2-1, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1-2, S2 is A2+1, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1-2, S2 is A2-1, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1+1, S2 is A2+2, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1+1, S2 is A2-2, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1-1, S2 is A2+2, S1>=0, S2>=0, S1<N, S2<N.
unPaso([A1, A2], [S1, S2], N):- S1 is A1-1, S2 is A2-2, S1>=0, S2>=0, S1<N, S2<N.


nat(0).
nat(N):- nat(N1), N is N1 + 1.
