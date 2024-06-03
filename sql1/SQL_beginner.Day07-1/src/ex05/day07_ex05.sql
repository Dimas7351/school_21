select distinct p.name  from person_order as ord
inner join person as p on p.id=ord.person_id
order by name
