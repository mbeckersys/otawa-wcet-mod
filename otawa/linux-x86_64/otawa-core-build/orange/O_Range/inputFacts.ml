
(* Taken from balance.ml! *)
(** Location in the source code. *)
module Loc = struct
  (** A location in the source code. *)
  type t = { file: string; (** File name. *)
	     line: int;    (** Line number. *)
	   }
  let make file line = { file = file; line = line }
  (** Prints a location. *)
  let print fmt loc = Format.fprintf fmt "%s:%d" loc.file loc.line
  let compare = Pervasives.compare
end

module LocMap = Map.Make(Loc)

type t = {
  upper_bounds : int LocMap.t
}

let of_ffx file =
  let xml = Xml.parse_file file in
  let rec traverse acc xml = match xml with
    | Xml.Element (name, attrs, children) ->
      let acc =
	if name = "loop"
	then
	  let get = Xml.attrib xml in
	  let file = get "source" in
	  let line = int_of_string (get "line") in
	  let max = int_of_string (get "maxcount") in
	  LocMap.add (Loc.make file line) max acc
	else acc in
      List.fold_left traverse acc children
    | Xml.PCData _ -> acc in
  let ub = traverse LocMap.empty xml in
  { upper_bounds = ub }

let none =
  { upper_bounds = LocMap.empty }

let upper_bound ff loc =
  if LocMap.mem loc ff.upper_bounds
  then Some (LocMap.find loc ff.upper_bounds)
  else None
