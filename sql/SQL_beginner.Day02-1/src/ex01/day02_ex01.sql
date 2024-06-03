select ds::date as missing_date from generate_series(
        '2022-01-01'::date,
        '2022-01-10',
        '1 day'
        ) as ds
left join
        (select * from person_visits
        where person_id=1 or person_id=2) as vis
on vis.visit_date=ds
where vis.visit_date is NULL
order by ds