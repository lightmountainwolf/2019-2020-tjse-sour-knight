

//最终觉得还是直接写子弹，无需写武器了，不同的武器就是不同的newBullet和moveBullet方式 

//放在.h文件里 
Vector<Sprite*>allBullet;//所有子弹，每一个子弹就是一个精灵 
void newBullet(float t);
void moveBullet(float t);

//.cpp里 
//计划任务
//处理子弹发射
this->schedule(schedule_selector(/**/::newBullet), 0.5);//每0.5秒产生一个 /*所在的类*/ 
this->schedule(schedule_selector(/**/::moveBullet), 0.1);//每0.1秒移动一次 
//定义 
void newBullet(float t) {
	auto spWeapon = this->getChildByTag(/**/);//实现在knight的位置创建子弹 
	Sprite* bullet = Sprite::create("bullet.png");
	bullet->setPosition(spWeapon->getPosition());
	this->addChild(bullet);
	this->allBullet.pushBack(bullet);//放到所有子弹里 
}

//这个是随着knignt移动向正上方发射子弹 
void moveBullet(float t) {
	for (int i = 0;i<allBullet.size();i++) 
	{
		auto nowbullet = allBullet.at(i);
		nowbullet->setPositionY(nowbullet->getPositionY() +  map->getMapSize().height/30);//上移地图的1/30 
		if (nowbullet->getPositionY > Director::getInstance()->getWinSize().height) { 
			nowbullet->removeFromParent();
			allBullet.eraseObject(nowbullet);//越界移除 
			i--;
		}
	}
}

//当有多个武器后 
void Warship::shoot(){
if(weaponType==1){
if(isScheduled(schedule_selector(/**/::newBullet1))){
//武器1已经启动
return;
}
if(isScheduled(schedule_selector(/**/::newBullet1))){
//若此时武器2已经启动，要关闭武器2
unschedule(schedule_selector(Warship::newBullet2))
}
//每0.3秒发射一次光子鱼雷
schedule(schedule_selector(/**/::newBullet1),0.5);
schedule(schedule_selector(/**/::moveBullet),0.1);
} 
else if(weaponType==2){
if(isScheduled(schedule_selector(/**/::newBullet2))){
//武器2已经启动
return;
}
if(isScheduled(schedule_selector(/**/::newBullet1))){
//若此时武器2已经启动，要关闭武器2
unschedule(schedule_selector(/**/::newBullet2))
}
schedule(schedule_selector(/**/::newBullet2),0.5);
schedule(schedule_selector(/**/::moveBullet),0.1);
} 

//还差碰撞检测 























