create function hello_world() returns text AS $$
BEGIN
    RETURN 'Hello, world!';
END;
$$ LANGUAGE plpgsql;

create function hello_cworld() returns int AS 'MODULE_PATHNAME', 'hello_cworld' LANGUAGE C;
