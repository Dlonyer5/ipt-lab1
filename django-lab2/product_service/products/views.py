from django.http import JsonResponse

def product_service(request):
    return JsonResponse({
        "service": "Product Service",
        "status": "running"
    })