#include "../scenes/MainScene.h"
#include "../scenes/StartScene.h"
#include "SimpleAudioEngine.h"
#include <cstring>
#include "../scenes/GameOverScene.h"
#include "../scenes/WinningScene.h"

#define COCOS2D_DEBUG 1
#define TRANSITION_TIME 0.5

USING_NS_CC;

using namespace std;

Label* label_score, * label_jumps;

Node* game_layer;
Node* menu_layer;

MainScene::MainScene(){}
MainScene::~MainScene(){}

Node* station;
Node* tree;
Node* stone;

bool tree_state = true;


Scene* MainScene::createScene() {

    auto main_scene = Scene::createWithPhysics();
    auto layer = MainScene::create();

    #if COCOS2D_DEBUG
        main_scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    #endif

    main_scene->getPhysicsWorld()->setGravity(CUSTOM_GRAVITY);
    main_scene->addChild(layer, 0, 0);

    return main_scene;
}


char* set_label(int flag, int _score){
    char text[50];
    if (flag == 1) {
        sprintf(text, "Score: %d", _score);
        return text;
    }
    if (flag == 2) {
        sprintf(text, "Jumps: %d", _score);
        return text;
    }
    return " ";
}

Vector<SpriteFrame*> getAnimation(const char *format, int count, int bothWay_flag) {
    auto spritecache = SpriteFrameCache::getInstance();
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= count; i++) {
        sprintf(str, format, i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    if(bothWay_flag){
        for(int i = count; i >= 1; i--) {
            sprintf(str, format, i);
            animFrames.pushBack(spritecache->getSpriteFrameByName(str));
        }
    }
    return animFrames;
}

void spriteAction(char* name, Node* _node, int sp_count, bool repeat_flag, float speed, int bothWay_Flag) {
    char sp_way[50];
    strcpy(sp_way, name);
    strcat(sp_way, "_%d.png");
    auto frames = getAnimation(sp_way, sp_count, bothWay_Flag);
    auto animation = Animation::createWithSpriteFrames(frames, speed);
    if (repeat_flag) _node->runAction(RepeatForever::create(Animate::create(animation)));
    else _node->runAction(Animate::create(animation));
}



bool MainScene::init() {
    
    score = 0;
    glibberFlag = 0;
    if ( !Layer::init() ) {
        return false;
    }
    
    game_layer = Node::create();
    game_layer->setName("game_layer");
    menu_layer = Node::create();
    menu_layer->setName("menu_layer");
    
    this->addChild(game_layer);
    this->addChild(menu_layer, 1);
    
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _screenSize = visibleSize;
    //_delta = Vec2(0,0);
    _center = Vec2(_screenSize.width * 0.5, _screenSize.height * 0.5);
    //_touch_start = Vec2(-1,-1); //Init State -1,-1 -> Not recorded yet
    //_touch_stop = Vec2(-1,-1);
   
    float playfield_width = _screenSize.width * 2.0; // make the x-boundry 2 times the screen width
    float playfield_height = _screenSize.height * 2.0; // make the y-boundry 2 times the screen height

    
    // SPRITESHEETS
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("res/spritesheets.png");
    game_layer->addChild(spritebatch, 1);
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("res/spritesheets.plist");
    
    
    //  MENU
    /* exit-button
    auto closeItem = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", CC_CALLBACK_1(MainScene::menuCloseCallback, this));
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2, origin.y + closeItem->getContentSize().height/2));
    menu_layer->addChild(closeItem, 3); */
    
    label_score = Label::createWithTTF(set_label(1, score), "fonts/Marker Felt.ttf", 32);
    label_score->setPosition(Vec2(label_score->getContentSize().width,
                                  visibleSize.height - label_score->getContentSize().height));
    
    label_jumps = Label::createWithTTF(set_label(2, jumps), "fonts/Marker Felt.ttf", 32);
    label_jumps->setPosition(Vec2(label_score->getContentSize().width,
                                 label_score->getPosition().y - label_jumps->getContentSize().height));
    
    menu_layer->addChild(label_score, 3);
    menu_layer->addChild(label_jumps, 3);
    
    
    //  BACKGROUND OBJECTS
    //      space background
    auto space = Sprite::create("res/space_bg.png");
    space->setScale(1.2);
    space->setPosition(Vec2(visibleSize.width/2  + origin.x, 200));
    game_layer->addChild(space);
    
    //      sun
    auto sun = Sprite::createWithSpriteFrameName("sun_1.png");
    sun->setPosition(-sun->getContentSize().width * 2.0,
                     -sun->getContentSize().height);
    spritebatch->addChild(sun);
    sun_way(sun);
    
    //      earth
    auto earth = Sprite::createWithSpriteFrameName("earth_1.png");
    earth->setPosition(_center.x + 500, _center.y);
    earth->setScale(0.5);
    spritebatch->addChild(earth);
    spriteAction("earth", earth, 3, true, 2.0f/8, 0);
    
    
    
    //  COLLIDE OBJECTS
    //      snail
    createSnail();
    
    //      tree
    tree = Sprite::createWithSpriteFrameName("tree_1.png");
    tree->setScale(0.5);
    auto treeBody = PhysicsBody::createBox(Size(tree->getContentSize().width,
                                                tree->getContentSize().height),
                                           PhysicsMaterial(1.0f, 0.0f, 0.0f));
    treeBody->setContactTestBitmask(0xFFFFFFFFF);
    treeBody->setDynamic(false);
    tree->setPhysicsBody(treeBody);
    tree->setName("tree");
    tree->setPosition(_center.x - 200, 250);
    tree_state = true;
    spritebatch->addChild(tree);



    //      station
    station = Sprite::createWithSpriteFrameName("station_1.png");
    station->setScale(0.5);
    auto stationBody = PhysicsBody::createBox(Size(station->getContentSize().width,
                                                   station->getContentSize().height/6),
                                              PhysicsMaterial(1.0f, 0.0f, 1.0f));
    stationBody->setDynamic(false);
    stationBody->setGravityEnable(false);
    station->setPhysicsBody(stationBody);
    station->setPosition(1440.74, _center.y);
    spritebatch->addChild(station);
    station->getPhysicsBody()->setPositionOffset(Vec2(0.0f,-station->getContentSize().height/4+15));//0.0f, -station->getContentSize().height/3
    station_way(station);


    //      ground
    auto ground = Sprite::create("res/ground.png");
    auto groundBody = PhysicsBody::createBox(Size(ground->getContentSize().width, 200.0f), PhysicsMaterial(1.0f, 0.0f, 0.9f));
    groundBody->setDynamic(false);
    groundBody->setTag(0);
    groundBody->setContactTestBitmask(0xFFFFFFFFF);
    ground->setPosition(Vec2(_center.x, 16.0f));
    ground->setPhysicsBody(groundBody);
    game_layer->addChild(ground, 1);
    
    //      walls
    auto wallBody1 = PhysicsBody::createBox(
                                            Size(32.0f, origin.y + visibleSize.height),
                                            PhysicsMaterial(0.0f, 0.0f, 0.0f) );
    auto wallBody2 = PhysicsBody::createBox(
                                            Size(32.0f,  origin.y + visibleSize.height*3),
                                            PhysicsMaterial(0.0f, 0.0f, 0.0f) );
    wallBody1->setDynamic(false);
    wallBody1->setPositionOffset(Vec2(visibleSize.width, visibleSize.height-visibleSize.height/2));
    wallBody1->setName("wall1");
    wallBody2->setDynamic(false);
    wallBody2->setPositionOffset(Vec2(-visibleSize.width/2, 0));
    wallBody2->setName("wall2");
    game_layer->addComponent(wallBody1);
    game_layer->addComponent(wallBody2);
    
    
    //  CAMERA
    game_layer->runAction(Follow::create( _snail->getSprite(),
                                            Rect( _center.x - playfield_width/2,
                                                 _center.y - playfield_height/4 ,
                                        playfield_width, playfield_height) ) );
    
    //  LISTNER
    auto listener = EventListenerTouchAllAtOnce::create();
    listener->onTouchesBegan = CC_CALLBACK_2(MainScene::onTouchesBegan, this);
    listener->onTouchesMoved = CC_CALLBACK_2(MainScene::onTouchesMoved, this);
    listener->onTouchesEnded = CC_CALLBACK_2(MainScene::onTouchesEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
   
    // HANDLES
    _handles = new ForceHandles(game_layer, CUSTOM_GRAVITY);
    
    this->scheduleUpdate();
    
    return true;
}

PhysicsBody *createSnailBody(Sprite *snail_sprite){

    PhysicsBody *old_body = snail_sprite->getPhysicsBody();

    PhysicsBody *snail_body = PhysicsBody::createBox(
                                                    Size(snail_sprite->getContentSize().width,
                                                    snail_sprite->getContentSize().height),
                                                    PhysicsMaterial(0.8f, 0.1f, 0.7f));
    snail_body->setMass(10.0f);
    snail_body->setContactTestBitmask(0xFFFFFFFFF);
    snail_body->setCategoryBitmask(0x02);    // 0011
    snail_body->setCollisionBitmask(0x01);   // 0001
    snail_body->setRotationEnable(false);
    snail_body->setTag(1);

    if (old_body) {
        snail_body->setVelocity(old_body->getVelocity());
    }

    return snail_body;
}

void MainScene::createSnail() {
    
    _snail = new Snail();
    _snail->getSprite()->setTexture("res/norm/snail_base.png");
    _snail->getSprite()->setPosition(Vec2(_center.x-_screenSize.width, 156.6f)); // log("%f ", _snail->getSprite()->getPosition().y);
    _snail->getSprite()->setScale(0.1, 0.1);
    _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
    _snail->getSprite()->setName("snail");
    game_layer->addChild(_snail->getSprite(), 2);
}

void changeTreePhBody() {
    Vec2 old_pos = tree->getPosition();
    auto treeBody = PhysicsBody::createBox(Size(tree->getContentSize().width,
                                                tree->getContentSize().height),
                                           PhysicsMaterial(1.0f, 0.6f, 0.0f));
    treeBody->setContactTestBitmask(0xFFFFFFFFF);
    treeBody->setDynamic(false);
    tree->setPhysicsBody(treeBody);
    tree->setPosition(old_pos);
}


void MainScene::update(float dt) {
   
    //score = abs(game_layer->getPosition().x);
    label_score->setString( set_label(1, score));
    label_jumps->setString(set_label(2, jumps));
    
    if (not _snail->air_state and _snail->getSprite()->getPhysicsBody()->getVelocity().y < 0) {
        _snail->getSprite()->setTexture("res/norm/snail_lands.png");
        _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
        _snail->base = false;
        _snail->air_state = true;
    }
    
    if(_snail->ground_state and not _snail->base) {
        _snail->getSprite()->setTexture("res/norm/snail_base.png");
        _snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));
        _snail->base = true;
    }
    
    if (not tree_state) changeTreePhBody();
    
    //TODO change when jump finished -> check if last jump successfull
    if (jumps == 0 && !_snail->air_state) {
        auto scene = GameOverScene::createScene();
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
    
    if (_snail->getSprite()->getPosition().x>1430&&_snail->getSprite()->getPosition().y>300) {
        auto scene = WinningScene::createScene();
        Director::getInstance( )->replaceScene( TransitionFade::create( TRANSITION_TIME, scene ) );
    }
}


bool MainScene::onContactBegin(PhysicsContact& contact) {
    auto nodeA = contact.getShapeA()->getBody()->getNode();
    auto nodeB = contact.getShapeB()->getBody()->getNode();
    
    if (nodeA && nodeB) {
        // ground, tree and snail with ContactTestBitmask(0xFFFFFFFFF)
        _snail->ground_state = true;
        _snail->air_state = false;
        
        if (nodeA->getName() == "tree" and nodeB->getName() == "snail" and tree_state) {
            tree_state = false;
            spriteAction("tree", nodeA, 4, false, 0.1, 0);
            score += 1;
            glibberFlag = 1;
        } else if (nodeB->getName() == "tree" and nodeA->getName() == "snail" and tree_state) {
            tree_state = false;
            spriteAction("tree", nodeB, 4, false, 0.1, 0);
            score += 1;
        }
   
    }
    
    return true;
}


void MainScene::sun_way(Node* sun) {
    
    auto moveTo0 = MoveTo::create(0.5, Vec2(-sun->getContentSize().width * 2.0,
                                            -sun->getContentSize().height));
    auto moveTo1 = MoveTo::create(10, Vec2(_center.x * 2.0, _center.y + 100));
    auto moveTo2 = MoveTo::create(10, Vec2(_screenSize.width * 2.0 + sun->getContentSize().width,
                                           -sun->getContentSize().height));
    auto seq = Sequence::create(moveTo0, moveTo1, moveTo2, nullptr);
    sun->runAction(RepeatForever::create(seq));
    
    spriteAction("sun", sun, 2, true, 2.0f/8, 0);
}


void MainScene::station_way(Node* station) {
    
    auto moveTo1 = MoveTo::create(0.5, Vec2(station->getPosition().x, station->getPosition().y + 50));
    auto move_ease_bounceInOut1 = EaseInOut::create(moveTo1->clone(), 0.2);
    auto moveTo2 = MoveTo::create(0.5, Vec2(station->getPosition().x, station->getPosition().y - 50));
    auto move_ease_bounceInOut2 = EaseInOut::create(moveTo2->clone(), 0.2);
    auto seq = Sequence::createWithTwoActions(move_ease_bounceInOut1, move_ease_bounceInOut2);
    
    station->runAction(RepeatForever::create(seq));
    spriteAction("station", station, 5, true, 0.3f, 1);
}


void MainScene::onTouchesBegan(const std::vector<Touch*> &touches, Event* event) {
    for (auto touch : touches) {
        if (touch != nullptr&&_snail->ground_state) {
            log("Touched: %f, %f",touch->getLocation().x, touch->getLocation().y);
            //TODO add camera Movement to Touch
            log("GameLayerPos: %f, %f",game_layer->getPosition().x, game_layer->getPosition().y);
            _touch_start = Vec2(-1,-1);
            _touch_stop = Vec2(-1,-1);
            Rect rect = _snail->getSprite()->getBoundingBox();
            rect.origin = rect.origin + game_layer->getPosition();
            if(rect.containsPoint(touch->getLocation())){
                _touch_start = touch->getLocation();
                log("First Point Logged");
            }
            
        }
    }
}

void MainScene::onTouchesMoved(const std::vector<Touch*> &touches, Event* event){
    for (auto touch : touches) {
        if (touch != nullptr&&_snail->ground_state) {
            /*_touch_stop = touch->getLocation();
            //_snail->getSprite()->setTexture("res/snail_touch.png");
            //_snail->getSprite()->setPhysicsBody(createSnailBody(_snail->getSprite()));*/
            
            //Only Save Point if Valid Start Point
            
            //Detect if first Move Point
            if(_touch_stop==Vec2(-1,-1)){       //TODO if delta high enough
                _snail->getSprite()->setTexture("res/norm/snail_touch.png");   //Activate Later -> Fix Bounding Box Problem
                log("Sprite Changed!");
                //TODO add & update arrow for force
                
            }else{
                //TODO arrow dashed -> not enough power to fly
            }
            
            //log("Move Point Logged");
            if(_touch_start!=Vec2(-1,-1)){  //TODO

                _touch_stop = touch->getLocation();
                _delta = _touch_start - _touch_stop;
                //Vec2 deltaN = _delta.getNormalized();
                //log("delta N: %f %f", deltaN.x, deltaN.y);
                //float xyRatio = deltaN.x/deltaN.y;
                //log("Delta: %f, %f",_delta.x, _delta.y);

                if(abs(_delta.x)>200)
                    _delta.x=(_delta.x<0)?(-200):(200);
                if(abs(_delta.y)>150)
                    _delta.y=(_delta.y<0)?(-150):(150);
                if(abs(_delta.x)<50)
                    _delta.x=(_delta.x<0)?(-50):(50);
                if(abs(_delta.y)<50)
                    _delta.y=(_delta.y<0)?(-50):(50);
                //Delta Maxs: x:200, y:150
                //Delta Mins: x:50,  y:50
                if(glibberFlag){
                    _delta.scale(0.5);
                    log("Scaled the Glibber");
                    //TODO alert
                }

                if(_delta.x<0){
                    _snail->getSprite()->setScale(-0.1, 0.1);
                }else{
                    _snail->getSprite()->setScale(0.1, 0.1);
                }

                _force = _delta;
                _force.scale(HELPING_FORCE);
                log("Force: (%f,%f)",_force.x,_force.y);
                log("Delta: (%f,%f)",_delta.x,_delta.y);


                //deltaOne = _touch_start.distance(_touch_stop);
                //log("DeltaOne: %f",deltaOne);
                //DeltaOne Max: 150 - 180
                //DeltaOne Min: 30 - 50
                
                
            }
        }
    }
}

void MainScene::onTouchesEnded(const std::vector<Touch*> &touches, Event* event) {
        for (auto touch : touches) {
            if(_touch_start!=_touch_stop && _touch_start!=Vec2(-1,-1) && _touch_stop!=Vec2(-1,-1)&&_snail->ground_state){
                _snail->getSprite()->getPhysicsBody()->applyForce(_force);
                
                jumps -= 1;
                _snail->getSprite()->setTexture("res/norm/snail_fly.png");
                _snail->base = false;
                _snail->ground_state = false;
                glibberFlag=(glibberFlag)?(0):(0);
                _touch_start = Vec2(-1,-1);
                _touch_stop = Vec2(-1,-1);

            }
        }
    //_touch_start = Vec2(-1,-1);
    //}
}


void MainScene::goToGameOverScene(Ref *sender) {
    this->cleanup();
    auto scene = GameOverScene::createScene();
    Director::getInstance()->replaceScene( TransitionFade::create(TRANSITION_TIME, scene) );
}


void MainScene::menuCloseCallback(Ref* pSender){
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}