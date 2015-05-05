(* The hybrid automaton *)
open Sexplib.Std
module List = Batteries.List
module String = Batteries.String

type 'a ha =
  | Ha of 'a
with sexp
