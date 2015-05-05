(* The water-tank example encoded into the ocaml type system *)

let  build_water_tank = 
  let open Language in

  (* The needed odes *)
  let ode1 = (Oeq ((Dot (Var "x")),
		   (Mult ((Avar "K"), (Minus ((Avar "h"),(Avar "x"))))))) in
  let ode2 = (Oeq ((Dot (Var "x")),(Real 0.0))) in
  let ode3 = (Oeq ((Dot (Var "x")),
		   (Mult ((Avar "K"), (Avar "x"))))) in
  let ode4 = ode2 in

  (* The locations *)
  let t1 = Loc ("t1", [ode1], [], (And ((Geq ((Var "x"),(int2nat 20))),
					(Leq ((Var "x"),(int2nat 100)))))) in

  let t2 = Loc ("t2", [ode2], [], (And ((Geq ((Var "x"),(int2nat 100))),
					(Leq ((Var "x"),(int2nat 100)))))) in

  let t3 = Loc ("t3", [ode3], [], (And ((Geq ((Var "x"),(int2nat 20))),
					(Leq ((Var "x"),(int2nat 100)))))) in

  let t4 = Loc ("t4", [ode4], [], (And ((Geq ((Var "x"),(int2nat 20))),
					(Leq ((Var "x"),(int2nat 20)))))) in

  (* The needed edges *)
  let e1 = Edge (t1,t2,(And ((Geq ((Var "x"),(int2nat 100))),
			     (Leq ((Var "x"),(int2nat 100))))),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "B")]) in

  let e2 = Edge (t2,t3,(True),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "OFF")]) in

  let e3 = Edge (t1,t3,(True),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "OFF")]) in

  let e4 = Edge (t3,t1,(True),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "ON")]) in

  let e5 = Edge (t3,t4,(And ((Geq ((Var "x"),(int2nat 20))),
			     (Leq ((Var "x"),(int2nat 20))))),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "C")]) in

  let e6 = Edge (t4,t1,(True),
		 [(Eq' ((Var "x"), (Var "x")))],
		 [(Event "ON")]) in

  let water_tank = Ha ([t1;t2;t3;t4],t4,[e1;e2;e3;e4;e5;e6]) in

  let () = Sexplib.Sexp.output_hum stdout (sexp_of_ha water_tank) in
  let () = print_endline "" in
  
  ()
