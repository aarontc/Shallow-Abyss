--
-- PostgreSQL database dump
--

-- Started on 2010-02-27 18:58:39 PST

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 1817 (class 1262 OID 16386)
-- Name: shadow; Type: DATABASE; Schema: -; Owner: -
--

CREATE DATABASE shadow WITH TEMPLATE = template0 ENCODING = 'UTF8' LC_COLLATE = 'C' LC_CTYPE = 'C';


\connect shadow

SET statement_timeout = 0;
SET client_encoding = 'UTF8';
SET standard_conforming_strings = off;
SET check_function_bodies = false;
SET client_min_messages = warning;
SET escape_string_warning = off;

--
-- TOC entry 316 (class 2612 OID 16457)
-- Name: plpgsql; Type: PROCEDURAL LANGUAGE; Schema: -; Owner: -
--

CREATE PROCEDURAL LANGUAGE plpgsql;


SET search_path = public, pg_catalog;

--
-- TOC entry 19 (class 1255 OID 16458)
-- Dependencies: 316 3
-- Name: update_modified_at_column(); Type: FUNCTION; Schema: public; Owner: -
--

CREATE FUNCTION update_modified_at_column() RETURNS trigger
    LANGUAGE plpgsql
    AS $$
begin
	NEW.modified_at = now();
	RETURN NEW;
END
$$;


SET default_tablespace = '';

SET default_with_oids = false;

--
-- TOC entry 1510 (class 1259 OID 16489)
-- Dependencies: 1795 3
-- Name: albums; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE albums (
    albumid integer NOT NULL,
    name character varying(255) NOT NULL,
    created_at timestamp with time zone DEFAULT ('now'::text)::timestamp with time zone NOT NULL,
    modified_at timestamp with time zone NOT NULL
);


--
-- TOC entry 1509 (class 1259 OID 16487)
-- Dependencies: 3 1510
-- Name: albums_albumid_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE albums_albumid_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- TOC entry 1820 (class 0 OID 0)
-- Dependencies: 1509
-- Name: albums_albumid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE albums_albumid_seq OWNED BY albums.albumid;


--
-- TOC entry 1506 (class 1259 OID 16397)
-- Dependencies: 1791 3
-- Name: artists; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE artists (
    artistid integer NOT NULL,
    name character varying(256),
    created_at timestamp with time zone DEFAULT ('now'::text)::timestamp with time zone NOT NULL,
    modified_at timestamp with time zone NOT NULL
);


--
-- TOC entry 1505 (class 1259 OID 16395)
-- Dependencies: 3 1506
-- Name: artists_artistid_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE artists_artistid_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- TOC entry 1821 (class 0 OID 0)
-- Dependencies: 1505
-- Name: artists_artistid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE artists_artistid_seq OWNED BY artists.artistid;


--
-- TOC entry 1508 (class 1259 OID 16461)
-- Dependencies: 1793 3
-- Name: files; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE files (
    fileid integer NOT NULL,
    path text NOT NULL,
    size integer NOT NULL,
    songid integer NOT NULL,
    ctime timestamp with time zone NOT NULL,
    mtime timestamp with time zone NOT NULL,
    created_at timestamp with time zone DEFAULT ('now'::text)::timestamp with time zone NOT NULL,
    modified_at timestamp with time zone NOT NULL
);


--
-- TOC entry 1822 (class 0 OID 0)
-- Dependencies: 1508
-- Name: COLUMN files.size; Type: COMMENT; Schema: public; Owner: -
--

COMMENT ON COLUMN files.size IS 'Size in bytes of the file';


--
-- TOC entry 1507 (class 1259 OID 16459)
-- Dependencies: 3 1508
-- Name: files_fileid_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE files_fileid_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- TOC entry 1823 (class 0 OID 0)
-- Dependencies: 1507
-- Name: files_fileid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE files_fileid_seq OWNED BY files.fileid;


--
-- TOC entry 1504 (class 1259 OID 16389)
-- Dependencies: 1789 3
-- Name: songs; Type: TABLE; Schema: public; Owner: -; Tablespace: 
--

CREATE TABLE songs (
    songid integer NOT NULL,
    artistid integer,
    title character varying(256) NOT NULL,
    albumid integer NOT NULL,
    created_at timestamp with time zone DEFAULT ('now'::text)::timestamp with time zone NOT NULL,
    modified_at timestamp with time zone NOT NULL
);


--
-- TOC entry 1503 (class 1259 OID 16387)
-- Dependencies: 1504 3
-- Name: songs_songid_seq; Type: SEQUENCE; Schema: public; Owner: -
--

CREATE SEQUENCE songs_songid_seq
    START WITH 1
    INCREMENT BY 1
    NO MAXVALUE
    NO MINVALUE
    CACHE 1;


--
-- TOC entry 1824 (class 0 OID 0)
-- Dependencies: 1503
-- Name: songs_songid_seq; Type: SEQUENCE OWNED BY; Schema: public; Owner: -
--

ALTER SEQUENCE songs_songid_seq OWNED BY songs.songid;


--
-- TOC entry 1794 (class 2604 OID 16492)
-- Dependencies: 1509 1510 1510
-- Name: albumid; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE albums ALTER COLUMN albumid SET DEFAULT nextval('albums_albumid_seq'::regclass);


--
-- TOC entry 1790 (class 2604 OID 16400)
-- Dependencies: 1505 1506 1506
-- Name: artistid; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE artists ALTER COLUMN artistid SET DEFAULT nextval('artists_artistid_seq'::regclass);


--
-- TOC entry 1792 (class 2604 OID 16464)
-- Dependencies: 1508 1507 1508
-- Name: fileid; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE files ALTER COLUMN fileid SET DEFAULT nextval('files_fileid_seq'::regclass);


--
-- TOC entry 1788 (class 2604 OID 16392)
-- Dependencies: 1503 1504 1504
-- Name: songid; Type: DEFAULT; Schema: public; Owner: -
--

ALTER TABLE songs ALTER COLUMN songid SET DEFAULT nextval('songs_songid_seq'::regclass);


--
-- TOC entry 1807 (class 2606 OID 16494)
-- Dependencies: 1510 1510
-- Name: albums_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY albums
    ADD CONSTRAINT albums_pkey PRIMARY KEY (albumid);


--
-- TOC entry 1801 (class 2606 OID 16420)
-- Dependencies: 1506 1506
-- Name: artists_name_key; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY artists
    ADD CONSTRAINT artists_name_key UNIQUE (name);


--
-- TOC entry 1803 (class 2606 OID 16402)
-- Dependencies: 1506 1506
-- Name: artists_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY artists
    ADD CONSTRAINT artists_pkey PRIMARY KEY (artistid);


--
-- TOC entry 1805 (class 2606 OID 16470)
-- Dependencies: 1508 1508
-- Name: files_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY files
    ADD CONSTRAINT files_pkey PRIMARY KEY (fileid);


--
-- TOC entry 1799 (class 2606 OID 16394)
-- Dependencies: 1504 1504
-- Name: songs_pkey; Type: CONSTRAINT; Schema: public; Owner: -; Tablespace: 
--

ALTER TABLE ONLY songs
    ADD CONSTRAINT songs_pkey PRIMARY KEY (songid);


--
-- TOC entry 1796 (class 1259 OID 16501)
-- Dependencies: 1504
-- Name: fki_songs_albumid_fkey; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX fki_songs_albumid_fkey ON songs USING btree (albumid);


--
-- TOC entry 1797 (class 1259 OID 16512)
-- Dependencies: 1504
-- Name: fki_songs_artistid_fkey; Type: INDEX; Schema: public; Owner: -; Tablespace: 
--

CREATE INDEX fki_songs_artistid_fkey ON songs USING btree (artistid);


--
-- TOC entry 1814 (class 2620 OID 16518)
-- Dependencies: 1510 19
-- Name: update_albums_modified_at; Type: TRIGGER; Schema: public; Owner: -
--

CREATE TRIGGER update_albums_modified_at
    BEFORE INSERT OR UPDATE ON albums
    FOR EACH ROW
    EXECUTE PROCEDURE update_modified_at_column();


--
-- TOC entry 1812 (class 2620 OID 16516)
-- Dependencies: 1506 19
-- Name: update_artists_modified_at; Type: TRIGGER; Schema: public; Owner: -
--

CREATE TRIGGER update_artists_modified_at
    BEFORE INSERT OR UPDATE ON artists
    FOR EACH ROW
    EXECUTE PROCEDURE update_modified_at_column();


--
-- TOC entry 1813 (class 2620 OID 16478)
-- Dependencies: 1508 19
-- Name: update_files_modified_at; Type: TRIGGER; Schema: public; Owner: -
--

CREATE TRIGGER update_files_modified_at
    BEFORE INSERT OR UPDATE ON files
    FOR EACH ROW
    EXECUTE PROCEDURE update_modified_at_column();


--
-- TOC entry 1811 (class 2620 OID 16514)
-- Dependencies: 19 1504
-- Name: update_songs_modified_at; Type: TRIGGER; Schema: public; Owner: -
--

CREATE TRIGGER update_songs_modified_at
    BEFORE INSERT OR UPDATE ON songs
    FOR EACH ROW
    EXECUTE PROCEDURE update_modified_at_column();


--
-- TOC entry 1810 (class 2606 OID 16471)
-- Dependencies: 1508 1798 1504
-- Name: files_songid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY files
    ADD CONSTRAINT files_songid_fkey FOREIGN KEY (songid) REFERENCES songs(songid) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1808 (class 2606 OID 16496)
-- Dependencies: 1504 1806 1510
-- Name: songs_albumid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY songs
    ADD CONSTRAINT songs_albumid_fkey FOREIGN KEY (albumid) REFERENCES albums(albumid) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1809 (class 2606 OID 16507)
-- Dependencies: 1802 1504 1506
-- Name: songs_artistid_fkey; Type: FK CONSTRAINT; Schema: public; Owner: -
--

ALTER TABLE ONLY songs
    ADD CONSTRAINT songs_artistid_fkey FOREIGN KEY (artistid) REFERENCES artists(artistid) ON UPDATE CASCADE ON DELETE CASCADE;


--
-- TOC entry 1819 (class 0 OID 0)
-- Dependencies: 3
-- Name: public; Type: ACL; Schema: -; Owner: -
--

REVOKE ALL ON SCHEMA public FROM PUBLIC;
REVOKE ALL ON SCHEMA public FROM postgres;
GRANT ALL ON SCHEMA public TO postgres;
GRANT ALL ON SCHEMA public TO PUBLIC;


-- Completed on 2010-02-27 18:58:39 PST

--
-- PostgreSQL database dump complete
--

