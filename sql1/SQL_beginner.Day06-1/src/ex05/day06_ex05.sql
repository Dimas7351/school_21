COMMENT ON TABLE person_discounts IS 'Table consists information of personal discounts for corresponding pizzerias';
COMMENT ON COLUMN person_discounts.id IS 'Unique id for each row, primary key';
COMMENT ON COLUMN person_discounts.person_id IS 'Unique identifier of a person. Foreign key to person_order table';
COMMENT ON COLUMN person_discounts.pizzeria_id IS 'Unique identifier of a pizzeria where person has corresponding discount. Foreign key to pizzeria table';
COMMENT ON COLUMN person_discounts.discount IS 'Discount value for person and corresponding pizzeria';