with gender_pizzeria_cte as (
    select piz.name, gender from person_order as ord
join person as p on ord.person_id = p.id
join menu as m on ord.menu_id = m.id
join pizzeria as piz on m.pizzeria_id = piz.id )

select name as pizzeria_name from gender_pizzeria_cte
where gender = 'female'
except
select name from gender_pizzeria_cte
where gender = 'male'
order by pizzeria_name
