select name from pizzeria
where id not in (select distinct pizzeria_id from person_visits);

select name from pizzeria as piz
where not exists (select distinct pizzeria_id from person_visits as vis
where pizzeria_id=piz.id)