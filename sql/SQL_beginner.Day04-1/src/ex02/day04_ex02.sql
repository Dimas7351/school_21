create view v_generated_dates as
select days::date as generated_date from generate_series(
         '2022-01-01',
         '2022-01-31',
         '1 day'::interval
 ) as days
order by generated_date;

