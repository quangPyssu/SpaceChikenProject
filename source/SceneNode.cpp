#include "SceneNode.h"

void SceneNode::attachChild(Ptr child)
{
    child->Parent = this;
    Children.emplace_back(std::move(child));
}

void SceneNode::PushToObject(SceneNode* tmp, SceneNode* Father)
{
    shared_ptr <SceneNode> here(tmp);
    Father->attachChild(here);
    here->Parent = Father;
}

SceneNode::Ptr SceneNode::detachChild(const SceneNode& node)
{
    auto found = std::find_if(Children.begin(), Children.end(),[&](Ptr& p) -> bool { return p.get() == &node; });
    assert(found != Children.end());
    Ptr result = std::move(*found);
    result->Parent = nullptr;
    Children.erase(found);
    return result;
}

void SceneNode::draw(RenderTarget& target, RenderStates states) const
{
    if (isDisable) return;
    states.transform *= getTransform();

    if (!isInvisible) drawCurrent(target, states);

    for (const auto& child : Children)
        if (child) child->draw(target, states);
}

void SceneNode::update(Event& event, Vector2f& MousePos)
{
    if (isDisable) return;
    
    if (isInteractable) updateCurrent(event, MousePos);

    for (const auto& child : Children) child->update(event, MousePos);
}

void SceneNode::takeTime()
{
    if (timerStart)
    {
        timerStart=max(timerStart-1,0);
        Disable();
    } else Able();

    if (isDisable) return;

    takeTimeCurrent();

    for (const auto& child : Children) child->takeTime();
}

void SceneNode::Disable()
{
    isDisable = true;
}

void SceneNode::Able()
{
    isDisable = false;
}