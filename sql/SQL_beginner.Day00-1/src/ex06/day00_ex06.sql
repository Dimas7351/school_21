SELECT 
    person_name,
    CASE
        WHEN person_name = 'Denis' THEN true
        ELSE false
    END AS check_name
FROM (
    SELECT 
        (SELECT name FROM person AS per WHERE per.id = ord.person_id) AS person_name
    FROM 
        person_order AS ord
    WHERE 
        (menu_id = 13 OR menu_id = 14 OR menu_id = 18)
        AND order_date = '2022-01-07'
) AS subquery;
