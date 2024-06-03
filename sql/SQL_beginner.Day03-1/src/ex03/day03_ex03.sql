with cte_populat_pizzeria as (
    select gender, piz.name from person_visits as vis
join person as p on vis.person_id = p.id
join pizzeria as piz on vis.pizzeria_id = piz.id
)

select name as pizzeria_name from (
select name,
     sum(case when gender='male' then 1 else 0 end) as male,
     sum(case when gender='female' then 1 else 0 end) as female
from cte_populat_pizzeria
group by name) as temp
where male!=female
order by 1



