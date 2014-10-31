```
json Stage{
	int id;
	vector<json Object{
		string id;
		int x, y;
	}> objects;
	vector<json Point{
		int x,y;
	}> spawn;
};

s = Stage::load("stage.json");

s.id
for(auto object : s.objects){
	object.x, object.y
}

s.save("stage_out.json");
```
