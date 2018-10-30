package finalmongo;

import com.mongodb.client.*; //for mongodatabase and mongocollection
import com.mongodb.client.model.*; // for bulkwrite and insertonemodel
import com.mongodb.MongoClient; //for Establishing connection

//import com.mongodb.client.model.Projections; 



import java.io.*;
import java.util.*;

import org.bson.*; //for Document
//import org.bson.conversions.Bson;

import static com.mongodb.client.model.Filters.*; //for providing filter in find()

public class Mongo {

	public static void main(String[] args) throws IOException {
		// TODO Auto-generated method stub

		MongoClient mongodb = new MongoClient("localhost", 27017);
		MongoDatabase db = mongodb.getDatabase("jacob");
		MongoCollection<Document> coll = db.getCollection("posts");
		
		 List<InsertOneModel<Document>> docs = new ArrayList<>();
		  
		  BufferedReader br = new BufferedReader(new
		  FileReader("/home/shubham/jacob.json"));
		  
		  String line; while ((line = br.readLine()) != null) { docs.add(new
		  InsertOneModel<>(Document.parse(line))); } coll.bulkWrite(docs, new
		  BulkWriteOptions().ordered(false)); docs.clear();

		// Display all
		FindIterable<Document> cursor = coll.find();

		for (Document doc : cursor) {
			System.out.println(doc);
		}
/*
		// count
		long count = coll.count(eq("author", "shubham"));
		System.out.println(count);

		
		// find with filter
		cursor = coll.find(eq("tags", "nvidia"));
		for (Document doc : cursor) {
			System.out.println(doc.toJson());
		}

	
		
		// Update one
		List<String> tag = new ArrayList<String>();
		tag.add("sup1");
		tag.add("sup2");
		tag.add("sup3");
		coll.updateOne(eq("author", "shubham"), new Document("$set", new Document("tags",tag )));
		coll.insertMany(tag);
		// Delete document
		coll.deleteOne(eq("author","SunilKumar"));
		
		cursor = coll.find(eq("author","shubham")).filter(Filters.eq("comment"));
		
		for (Document doc : cursor) {
			System.out.println(doc);
		}
		*/
	}

}
