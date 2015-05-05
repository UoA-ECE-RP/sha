(* Author: Avinash Malik *)
(* Tue May  5 14:03:20 NZST 2015 *)

open Sexplib.Std
module List = Batteries.List
module String = Batteries.String

(* Natural numbers are encoded 
   as an inductive dataype 
   to be safe*)
type nat =
  | Z
  | S of nat
with sexp

type var = 
  | Var of string
with sexp

(* These are the invariant/guard types *)
type expr = 
  | Leq of var * nat
  | Geq of var * nat
  | Gt of var * nat
  | Lt of var * nat
  | And of expr * expr
  | True
  | False
with sexp

(* FIXME: Extend this as needed *)
type arithexpr = 
  | Avar of string
  | Real of float
  | Plus of arithexpr * arithexpr
  | Minus of arithexpr * arithexpr
  | Div of arithexpr * arithexpr
  | Mult of arithexpr * arithexpr
  | Mod of arithexpr * arithexpr
with sexp

type dot = 
  | Dot of var 
with sexp

type ode = 
  | Oeq of dot * arithexpr	(* (= (dot x) (x + 10)) *)
with sexp

type cfun = 
  | Ceq of var * arithexpr
with sexp


(* The invariant is just the bool expr type *)
type invariant = expr
with sexp

(* These are the events of the hybrid automaton *)
type event =
  | Event of string
with sexp

type guard = expr
with sexp

type update = 
  | Eq of var * nat 		(* x'= 10 *)
  | Eq' of var * var		(* x' = x *)
with sexp
  
(* This is the location of the hybrid automaton *)
type loc = 
  | Loc of string * ode list * cfun list * invariant
and
  sloc = loc
and
  edge =
  | Edge of loc * loc * guard * update list * event list
with sexp

(* The hybrid automaton itself *)
(* All checking should be done on this automaton. The Ha should be
   well-formed and should be synchornous for the code generation to be
   successful*)
type ha =
  | Ha of loc list * sloc * edge list
with sexp


(* Helper function to convert nat to int *)
let nat2int ff = 
  let rec n2i count = function
    | Z -> count
    | S x -> n2i (count + 1) x in
  n2i 0 ff

(* Helper function to convert int to nat *)
let int2nat i = 
  let rec i2n ff = function
    | 0 -> ff
    | _ as x when x > 0-> i2n (S ff) (x-1)
    | _ as s -> failwith ("Negative nats not supported: " ^ (string_of_int s))in
  i2n Z i
