cities([1,2,3,4]).
road(1,2, 10).  % road between cities 1 and 2 of 10km
road(1,4, 20).
road(2,3, 25).
road(3,4, 12).

mainroads(K,M)


% We want to find a set of main roads that connect all cities spending at most a certain number of kilometers.
% Program in Prolog a new predicate mainroads(K,M) which means that,
% for the given K, M is a subset of the roads that connects all cities forming a tree and total length of the roads in M is at most K
% (note that being a tree means that there are no cycles).
