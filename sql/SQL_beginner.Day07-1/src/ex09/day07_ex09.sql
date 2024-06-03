with cte_calc as (
    select address, round(max(age)-(min(age)*1.0/max(age)),2) as formula,
           round(avg(age),2) as average
    from person
    group by address
    order by address)

select *, (
    case when formula>average then true
         else false end) as comparison
from cte_calc