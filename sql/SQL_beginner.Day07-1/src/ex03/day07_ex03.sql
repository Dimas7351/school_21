WITH
    cte_visits as
        (
            select piz.name, count(*) as count
            from person_visits as vis
                     join pizzeria as piz on vis.pizzeria_id = piz.id
            group by piz.name
            order by count desc
        ),

    cte_orders as
        (
            select piz.name, count(*) as count
            from person_order as vis
                     join menu as m on vis.menu_id = m.id
                     join pizzeria as piz on m.pizzeria_id = piz.id
            group by piz.name
            order by count desc
        )

select piz.name, coalesce(ord.count,0)+coalesce(vis.count,0) as total_count
from pizzeria as piz
         full join cte_visits as vis on piz.name=vis.name
         full join cte_orders as ord on piz.name=ord.name
order by total_count desc, name