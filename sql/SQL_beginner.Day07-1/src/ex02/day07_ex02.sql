WITH
    cte_visits as
        (
            select piz.name, count(*) as count, 'visit' as action_type
            from person_visits as vis
                     join pizzeria as piz on vis.pizzeria_id = piz.id
            group by piz.name
            order by count desc
            limit 3
        ),

    cte_orders as
        (
            select piz.name, count(*) as count, 'order' as action_type
            from person_order as vis
                     join menu as m on vis.menu_id = m.id
                     join pizzeria as piz on m.pizzeria_id = piz.id
            group by piz.name
            order by count desc
            limit 3
        )

select * from cte_orders
union
select * from cte_visits
order by action_type, count desc