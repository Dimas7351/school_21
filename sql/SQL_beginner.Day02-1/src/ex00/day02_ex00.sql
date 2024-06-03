select name, rating from pizzeria as p
left join person_visits as v
on p.id = v.pizzeria_id
where v.pizzeria_id is NULL