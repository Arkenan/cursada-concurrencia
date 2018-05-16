- module(listas).
- export([sum/1, map/2]).

sum([]) -> 0;
sum([H | T]) -> H + sum(T).

% No importa la F para el primero, así que va un "_" para indicar que va un arg.
map(_, []) -> [];
map(F, [H | T]) -> [F(H) | map(F, T)].
